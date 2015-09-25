#include "sani/core/cvar/cvar_record_generator.hpp"
#include "sani/core/cvar/cvar_tokenizer.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "sani/core/cvar/cvar_emitter.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/platform/file_system.hpp"

namespace sani {

	CVarCompiler::CVarCompiler(const String& configurationRootFolder, io::FileSystem& fileSystem) : configurationRootFolder(configurationRootFolder),
																						            fileSystem(fileSystem) {
	}

	void CVarCompiler::pushError(const String& error) {
		errorBuffer.push(error);
	}

	bool CVarCompiler::hasErrors() const {
		return errorBuffer.size() != 0;
	}
	String CVarCompiler::getNextError() {
		String error(errorBuffer.top());
		errorBuffer.pop();

		return error;
	}

	void CVarCompiler::generateCVars(std::list<CVar>& cvars, std::list<CVarToken>& tokens) {
		CVarParser parser;

		std::list<cvarlang::IntermediateCVar> intermediateCVar;
		std::list<cvarlang::IntermediateRequireStatement> intermediateRequireStatement;
		std::list<CVarRequireStatement> statements;

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
			}
			else if (i->getType() == cvarlang::TokenType::Require) {
				// So, the require token class has 2 variants, the one 
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
	void CVarCompiler::generateRecords(std::list<CVarRecord>& records, std::list<CVarToken>& tokens) {
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
			while (tokenizer.hasErrors()) pushError(tokenizer.getNextError());

			return;
		}
		
		// Generate records.
		CVarRecordGenerator recordGenerator;
		recordGenerator.generateRecords(tokens, cvars, records);
	}

	CVarCompiler::~CVarCompiler() {
	}
}