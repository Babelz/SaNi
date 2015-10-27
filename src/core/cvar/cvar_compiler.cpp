#include "sani/core/cvar/cvar_tokenizer.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "sani/core/cvar/cvar_linker.hpp"
#include "sani/core/cvar/link_record.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/debug.hpp"

namespace sani {

	CVarCompiler::CVarCompiler() {
		generateStatementGenerators();
	}

	void CVarCompiler::generateStatementGenerators() {
		using namespace std::placeholders;

		statementGenerators.push_back(
			GEN_REQUIRE_STATEMENT_GENERATOR(intermediateCondition.lhs.size() > 0 && intermediateCondition.rhs.size() == 0,
			std::bind(&sani::CVarCompiler::generateConstCVarBoolExpression, this, _1, _2, _3)));

		statementGenerators.push_back(
			GEN_REQUIRE_STATEMENT_GENERATOR(intermediateCondition.lhs.size() > 0 && intermediateCondition.lhsIsConst && intermediateCondition.rhs.size() == 0,
			std::bind(&sani::CVarCompiler::generateConstBoolConstExpression, this, _1, _2, _3)));
		
		statementGenerators.push_back(
			GEN_REQUIRE_STATEMENT_GENERATOR(intermediateCondition.lhsIsConst && intermediateCondition.rhsIsConst,
			std::bind(&sani::CVarCompiler::generateConstConstExpression, this, _1, _2, _3)));

		statementGenerators.push_back(
			GEN_REQUIRE_STATEMENT_GENERATOR(intermediateCondition.rhsIsConst && !intermediateCondition.lhsIsConst,
			std::bind(&sani::CVarCompiler::generateConstCVarExpression, this, _1, _2, _3)));

		statementGenerators.push_back(
			GEN_REQUIRE_STATEMENT_GENERATOR(!intermediateCondition.rhsIsConst && intermediateCondition.lhsIsConst,
			std::bind(&sani::CVarCompiler::generateCVarConstExpression, this, _1, _2, _3)));

		statementGenerators.push_back(
			GEN_REQUIRE_STATEMENT_GENERATOR(!intermediateCondition.rhsIsConst && !intermediateCondition.lhsIsConst,
			std::bind(&sani::CVarCompiler::generateCVarCVarExpression, this, _1, _2, _3)));
	}

	void CVarCompiler::copyErrors(CVarParser* parser) {
		while (parser->hasErrors()) errorBuffer.push(parser->getNextError());
	}
	void CVarCompiler::copyErrors(CVarTokenizer* tokenizer) {
		while (tokenizer->hasErrors()) errorBuffer.push(tokenizer->getNextError());
	}
	void CVarCompiler::copyErrors(CVarLinker* linker) {
		while (linker->hasErrors()) errorBuffer.push(linker->getNextError());
	}

	bool CVarCompiler::hasErrors() const {
		return errorBuffer.size() != 0;
	}
	String CVarCompiler::getNextError() {
		String error(errorBuffer.top());
		errorBuffer.pop();

		return error;
	}

	void CVarCompiler::generateCVars(CVarList& cvars, RecordList& records, TokenList& tokens) {
		// 1) Process token
		// 2) Parse it
		// 3) Check for errors
		// 4) Emit cvar or statement
		// 5) generate record

		CVarParser parser;

		std::list<cvarlang::IntermediateCVar> intermediateCVar;
		std::list<IntermediateRequireStatement> intermediateRequireStatement;
		std::list<CVarRequireStatement> statements;
		// Current scope level.
		size_t scope = 0;

		// Go trough each token.
		auto i = tokens.begin();

		while (i != tokens.end()) {
			// Only process declaration and require tokens.
			// Anything but these are just pure garbage.

			if (i->getType() == cvarlang::TokenType::Declaration) {
				cvarlang::IntermediateCVar intermediateCVar;

				parser.parseCvar(i->getLine(), intermediateCVar);

				if (parser.hasErrors()) copyErrors(&parser);

				// Emit cvar.
				generateCVar(cvars, statements, &intermediateCVar);

				/*
							TODO

					Add volatile keyword checking
					for synced variables

				*/

				// Emit record.
				generateRecord(records, *i, cvars.back());
				
			} else if (i->getType() == cvarlang::TokenType::Require) {
				// So, the require token class has 2 variants, the one 
				// that starts a require statement (require([condition]) and 
				// the one that ends a block, that is just the plain require keyword in use.
				// We need to track that the user closes the scopes before the tokens end,
				// or we are fucked.

				IntermediateRequireStatement intermediateRequireStatement;
				String message;

				// Check if the next one is a message statement.
				auto next = std::next(i, 1);

				if (next != tokens.end()) {
					if ((next)->getType() == cvarlang::TokenType::Message) {
						message = (next)->getLine();

						parser.parseRequireStatement(i->getLine(), message, intermediateRequireStatement);

						i++;
					}
				} else {
					parser.parseRequireStatement(i->getLine(), message, intermediateRequireStatement);
				}

				if (intermediateRequireStatement.blockEnding) {
					if (scope > 0) {
						statements.remove(statements.back());
						scope--;
					}
				} else {
					generateRequireStatement(statements, cvars, &intermediateRequireStatement);
					scope++;
				}
			}

			// Do not emit warnings for invalid tokens, as the 
			// tokenizer has done this already.
			// (avoid duplicated error messages)

			i++;
		}

		// Emit possible scope errors and 
		// copy possible parsing errors to this level.
		if (scope > 0) {
			auto last = tokens.begin();
			std::advance(last, tokens.size() - 1);

			errorBuffer.push(SANI_ERROR_MESSAGE("require scope was not closed at the end of require block at file " + last->getFilename()));
		}

		if (parser.hasErrors()) copyErrors(&parser);
	}

	void CVarCompiler::generateCVar(CVarList& cvars, StatementList& statements, const IntermediateCVar* intermediateCVar) const  {
		// TODO: add volatile keyword checks for synced cvars.
		cvars.push_back(CVar(statements, intermediateCVar->type, intermediateCVar->name, true, intermediateCVar->value));
	}
	void CVarCompiler::generateRecord(RecordList& records, const CVarToken& token, const CVar& cvar) const {
		records.push_back(CVarRecord(token, cvar));
	}

	void CVarCompiler::generateRequireStatement(std::list<CVarRequireStatement>& statements, CVarList& cvars, const IntermediateRequireStatement* intermediateRequireStatement) {
		std::vector<CVarCondition> conditions;

		/*
			TODO: missing the boolean not (!) operator for bool expressions.
			They could come handy.
		*/

		for (const cvarlang::IntermediateCondition& intermediateCondition : intermediateRequireStatement->conditions) {
			if (intermediateCondition.lhs.size() > 0 || intermediateCondition.rhs.size() > 0) {
				Condition condition;

				for (RequireStatementGenerator& generator : statementGenerators) {
					if (generator.condition(intermediateCondition)) {
						generator.generate(intermediateCondition, condition, cvars);
					}
				}

				conditions.push_back(CVarCondition(intermediateCondition.logicalOperator, condition));
			}
		}

		statements.push_back(CVarRequireStatement(conditions, intermediateRequireStatement->message));
	}

	void CVarCompiler::generateConstConstExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars) const  {
		CVar lhs(intermediateCondition.lhsType, String("___TEMP_CVAR___"), false, intermediateCondition.lhs);
		CVar rhs(intermediateCondition.rhsType, String("___TEMP_CVAR___"), false, intermediateCondition.rhs);

		condition = [&lhs, &rhs]() {
			return lhs == rhs;
		};
	}
	void CVarCompiler::generateConstCVarExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars) const  {
		CVar lhs(intermediateCondition.lhsType, String("___TEMP_CVAR___"), false, intermediateCondition.lhs);
		CVar rhs(intermediateCondition.rhsType, String("___TEMP_CVAR___"), false, intermediateCondition.rhs);

		generateCondition(intermediateCondition, condition, lhs, rhs);
	}
	void CVarCompiler::generateCVarConstExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars) {
		CVar* lhs = findCVar(cvars, intermediateCondition.lhs);
		if (lhs == nullptr) return;

		CVar rhs(intermediateCondition.rhsType, String("___TEMP_CVAR___"), false, intermediateCondition.rhs);

		generateCondition(intermediateCondition, condition, *lhs, rhs);
	}
	void CVarCompiler::generateConstCVarBoolExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars) {
		CVar lhs(intermediateCondition.lhsType, String("___TEMP_CVAR___"), false, intermediateCondition.lhs);

		CVar* rhs = findCVar(cvars, intermediateCondition.rhs);
		if (rhs == nullptr) return;

		generateCondition(intermediateCondition, condition, lhs, *rhs);
	}
	void CVarCompiler::generateConstBoolConstExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars) const  {
		if (intermediateCondition.lhsIsConst) {
			CVar lhs(intermediateCondition.lhsType, String("___TEMP_CVAR___"), false, intermediateCondition.lhs);
			CVar rhs(intermediateCondition.lhsType, String("___TEMP_CVAR___"));

			condition = [&lhs, &rhs]() {
				return lhs >= rhs;
			};
		}
	}
	void CVarCompiler::generateCVarCVarExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars)  {
		CVar* lhs = findCVar(cvars, intermediateCondition.lhs);
		if (lhs == nullptr) return;

		CVar* rhs = findCVar(cvars, intermediateCondition.rhs);
		if (rhs == nullptr) return;

		generateCondition(intermediateCondition, condition, *lhs, *rhs);
	}

	void CVarCompiler::generateCondition(const IntermediateCondition& intermediateCondition, Condition& condition, CVar& lhs, CVar& rhs) const  {
		if (intermediateCondition.conditionalOperator == cvarlang::ConditionalOperators::Equal) {
			condition = [&lhs, &rhs]() {
				return lhs == rhs;
			};
		} else if (intermediateCondition.conditionalOperator == cvarlang::ConditionalOperators::NotEqual) {
			condition = [&lhs, &rhs]() {
				return lhs != rhs;
			};
		} else if (intermediateCondition.conditionalOperator == cvarlang::ConditionalOperators::Smaller) {
			condition = [&lhs, &rhs]() {
				return lhs < rhs;
			};
		} else if (intermediateCondition.conditionalOperator == cvarlang::ConditionalOperators::SmallerOrEqual) {
			condition = [&lhs, &rhs]() {
				return lhs <= rhs;
			};
		} else if (intermediateCondition.conditionalOperator == cvarlang::ConditionalOperators::Greater) {
			condition = [&lhs, &rhs]() {
				return lhs > rhs;
			};
		} else if (intermediateCondition.conditionalOperator == cvarlang::ConditionalOperators::GreaterOrEqual) {
			condition = [&lhs, &rhs]() {
				return lhs >= rhs;
			};
		}
	}

	CVar* CVarCompiler::findCVar(CVarList& cvars, const String& name) {
		if (name.size() == 0) return nullptr;

		for (CVar& cvar : cvars) {
			if (cvar.getName() == name) {
				return &cvar;
			}
		}

		errorBuffer.push(SANI_ERROR_MESSAGE("no cvar with name " + name + " was found at this time"));

		return nullptr;
	}

	void CVarCompiler::compile(const String& filename, std::list<CVarFile>& files, std::list<CVar>& cvars, std::list<CVarRecord>& records) {
		// Link files.
		CVarLinker linker;
		LinkRecord linkRecord;
		linker.link(filename, files, &linkRecord);

		if (linker.hasErrors()) {
			copyErrors(&linker);
		}

		// Get linked files.
		std::list<CVarFile*> linkedFiles;
		linkedFiles.push_back(linkRecord.getRoot());

		while (linkRecord.hasLinks()) linkedFiles.push_back(linkRecord.getNextLink());

		// Generate tokens from linked files.
		CVarTokenizer tokenizer;

		std::list<CVarToken> tokens;
		tokenizer.tokenize(linkedFiles, tokens);

		if (tokenizer.hasErrors()) {
			copyErrors(&tokenizer);
		}

		// Try parse and emit.
		generateCVars(cvars, records, tokens);
	}

	CVarCompiler::~CVarCompiler() {
	}
}