#include "sani/core/cvar/cvar_record_generator.hpp"
#include "sani/core/cvar/cvar_tokenizer.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "sani/core/cvar/cvar_emitter.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/platform/file_system.hpp"

namespace sani {

	CVarCompiler::CVarCompiler(const String& configurationRootFolder, io::FileSystem& fileSystem, const bool synced) : configurationRootFolder(configurationRootFolder),
																													   fileSystem(fileSystem),
																													   synced(synced) {
	}

	void CVarCompiler::copyErrors(CVarParser* parser) {
		while (parser->hasErrors()) errorBuffer.push(parser->getNextError());
	}
	void CVarCompiler::copyErrors(CVarTokenizer* tokenizer) {
		while (tokenizer->hasErrors()) errorBuffer.push(tokenizer->getNextError());
	}

	void CVarCompiler::pushError(const String& message) {
		errorBuffer.push(message);
	}

	bool CVarCompiler::hasErrors() const {
		return errorBuffer.size() != 0;
	}
	String CVarCompiler::getNextError() {
		String error(errorBuffer.top());
		errorBuffer.pop();

		return error;
	}

	void CVarCompiler::generateCVars(std::list<CVar>& cvars, std::list<CVarRecord>& records, std::list<CVarToken>& tokens) {
		// 1) Process token
		// 2) Parse it
		// 3) Check for errors
		// 4) Emit cvar or statement
		// 5) generate record

		CVarParser parser;

		std::list<cvarlang::IntermediateCVar> intermediateCVar;
		std::list<cvarlang::IntermediateRequireStatement> intermediateRequireStatement;
		std::list<CVarRequireStatement> statements;
		// Current scope level. Gets decreased when require keyword is found,
		// and gets increased when require statement is found.
		size_t scope = 0;		

		// Go trough each token.
		auto i = tokens.begin();
		while (i != tokens.end()) {
			// Only process declaration and require tokens.
			// Anything but these are just pure garbage.
			// We still keep these tokens for the parsing process.
			// Who knows if we need them some day (when the lexical analyzer evolves OSLT)
			if (i->getType() == cvarlang::TokenType::Declaration) {
				cvarlang::IntermediateCVar intermediateCVar;

				parser.parseCvar(i->getLine(), intermediateCVar);

				if (parser.hasErrors()) copyErrors(&parser);

				// Emit cvar.
				generateCVar(cvars, statements, &intermediateCVar);

				if (synced) {
					// Emit record.
					generateRecord(records, *i, cvars.back());
				}
			}
			else if (i->getType() == cvarlang::TokenType::Require) {
				// So, the require token class has 2 variants, the one 
				// that starts a require statement (require([condition]) and 
				// the one that ends a block, that is just the plain require keyword in use.
				// We need to track that the user closes the scopes before the tokens end,
				// or we are fucked.

				cvarlang::IntermediateRequireStatement intermediateRequireStatement;
				String message;

				// Check if the next one is a message statement.
				auto next = std::next(i, 1);

				if (next != tokens.end()) {
					if ((next)->getType() == cvarlang::TokenType::Message) {
						message = (next)->getLine();

						i++;
					}
				}

				parser.parseRequireStatement(i->getLine(), message, intermediateRequireStatement);
				
				if (intermediateRequireStatement.blockEnding) {
					if (scope > 0) {
						statements.remove(statements.back());
						scope--;
					}

					continue;
				}

				generateRequireStatement(statements, &intermediateRequireStatement);
			}
			else if (i->getType() == cvarlang::TokenType::Message) {
				pushError(SANI_ERROR_MESSAGE("did not except a message statement at this time"));
			}

			i++;

			if (hasErrors()) return;
		}

		// Generate cvars.
		CVarEmitter emitter;
		emitter.emit(tokens, cvars);
	}

	void CVarCompiler::generateCVar(std::list<CVar>& cvars, std::list<CVarRequireStatement>& statements, const cvarlang::IntermediateCVar* intermediateCVar) {
		if (intermediateCVar->type == sani::cvarlang::StringVal) {
			cvars.push_back(CVar(statements, intermediateCVar->type, intermediateCVar->name, synced,
								 intermediateCVar->value));
		} else if (intermediateCVar->type == sani::cvarlang::IntVal) { 
			cvars.push_back(CVar(statements, intermediateCVar->type, intermediateCVar->name, synced, 
								 std::stoi(intermediateCVar->value.c_str())));
		} else if (intermediateCVar->type == sani::cvarlang::FloatVal) {
			cvars.push_back(CVar(statements, intermediateCVar->type, intermediateCVar->name, synced,
								 static_cast<float32>(std::atof(intermediateCVar->value.c_str()))));
		} else if (intermediateCVar->type == sani::cvarlang::DoubleVal) {
			cvars.push_back(CVar(statements, intermediateCVar->type, intermediateCVar->name, synced,
								 std::atof(intermediateCVar->value.c_str())));
		} else {
			pushError(SANI_ERROR_MESSAGE("was not excepting a value type of NoValue at this time"));
		}
	}
	void CVarCompiler::generateRecord(std::list<CVarRecord>& records, const CVarToken& token, const CVar& cvar) const {
		records.push_back(CVarRecord(token, cvar));
	}

	void CVarCompiler::generateRequireStatement(std::list<CVarRequireStatement>& statements, const cvarlang::IntermediateRequireStatement* intermediateRequireStatement) {
		std::vector<CVarCondition> conditions;

		for (const cvarlang::IntermediateCondition& condition : intermediateRequireStatement->conditions) {
			if (condition.lhs.size() > 0 && condition.rhs.size() > 0) {
				if (condition.lhsIsConst && condition.rhsIsConst) {
					// Const oper const
				} else if (condition.rhsIsConst && !condition.lhsIsConst) {
					// const oper cvar
				} else if (!condition.rhsIsConst && condition.lhsIsConst) {
					// cvar oper const
				}
			} else if (condition.lhs.size() > 0 && condition.rhs.size() == 0) {
			} else {
				pushError(SANI_ERROR_MESSAGE("invalid require expression"));
			}
		}

		statements.push_back(CVarRequireStatement(conditions, intermediateRequireStatement->message));
	}
	
	void CVarCompiler::compile(std::list<CVar>& cvars, std::list<CVarRecord>& records) {
		// Load all files.
		CVarLoader loader(configurationRootFolder, fileSystem);
		
		std::list<CVarFile> files;
		loader.load(files);

		// Generate tokens from lines.
		CVarTokenizer tokenizer;

		std::list<CVarToken> tokens;
		tokenizer.tokenize(files, tokens);

		if (tokenizer.hasErrors()) {
			copyErrors(&tokenizer);

			return;
		}

		generateCVars(cvars, records, tokens);
	}

	CVarCompiler::~CVarCompiler() {
	}
}