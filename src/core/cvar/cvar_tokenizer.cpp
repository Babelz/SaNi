#include "sani/core/cvar/cvar_tokenizer.hpp"
#include "sani/core/cvar/cvar_lang.hpp"

namespace sani {

	CVarTokenizer::CVarTokenizer() {
	}

	void CVarTokenizer::pushError(const String& error) {
		errorBuffer.push(error);
	}

	bool CVarTokenizer::hasErrors() const {
		return errorBuffer.size() != 0;
	}
	String CVarTokenizer::getNextError() {
		String error(errorBuffer.top());
		errorBuffer.pop();

		return error;
	}

	void CVarTokenizer::tokenize(const std::list<CVarFile>& files, std::vector<CVarToken>& tokens) {
		/*
			Just tokenize all the files, don't stop if errors are found.
			This is just to show all the errors found, not the first one.
		*/
		
		// Go trough each file...
		for (const CVarFile& file : files) {
			// Go trough each line...
			for (size_t i = 0; i < file.getLinesCount(); i++) {
				const String& line = file.lineAtIndex(i);
				cvarlang::TokenType type = cvarlang::TokenType::Invalid;

				if (line.size() == 0 || cvarlang::lang::startsWithComment(line)) continue;
				
				// Check what type the line could be.
				if (cvarlang::lang::startsWithInclude(line)) {
					if (cvarlang::lang::isValidInclude(line)) type = cvarlang::TokenType::Include;
					else									  pushError(SANI_ERROR_MESSAGE("invalid include statement at line " + std::to_string(i) + ", at file " + file.getFilename()));
				}
				else if (cvarlang::lang::startsWithRequire(line)) {
					if (cvarlang::lang::isValidRequire(line)) type = cvarlang::TokenType::Require;
					else									  pushError(SANI_ERROR_MESSAGE("invalid require statement at line " + std::to_string(i) + ", at file " + file.getFilename()));
				}
				else if (cvarlang::lang::isDeclaration(line)) {
					if (cvarlang::lang::isValidDeclaration(line)) type = cvarlang::TokenType::Declaration;
					else										  pushError(SANI_ERROR_MESSAGE("invalid declaration at line" + std::to_string(i) + ", at file " + file.getFilename()));
				} else if (cvarlang::lang::isEmptyOrWhitespace(line)) {
					type = cvarlang::TokenType::EmptyOrComment;
				}

				if (type == cvarlang::TokenType::Invalid) {
					// Push error, invalid line.
					pushError(SANI_ERROR_MESSAGE("invalid token at line " + std::to_string(i) + ", at file " + file.getFilename()));
				} else if (!hasErrors()) {
					// Check for errors before creating a token, as some
					// might have been recorded. 

					// Should be a valid token.
					CVarToken token = CVarToken(type, i, file.getFilename(), line);
				}
			}
		}
	}

	CVarTokenizer::~CVarTokenizer()  {
	}
}