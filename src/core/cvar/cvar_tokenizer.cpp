#include "sani/core/cvar/cvar_tokenizer.hpp"
#include "sani/core/utils/string_utils.hpp"
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

	void CVarTokenizer::tokenize(const std::list<CVarFile>& files, std::list<CVarToken>& tokens) {
		/*
			Just tokenize all the files, don't stop if errors are found.
			This is just to show all the errors found, not the first one.
		*/
		
		bool lastRequire = false;

		// Go trough each file...
		for (const CVarFile& file : files) {
			// Go trough each line...
			for (size_t i = 0; i < file.getLinesCount(); i++) {
				const String& line = file.lineAtIndex(i);
				cvarlang::TokenType type = cvarlang::TokenType::Invalid;

				if (line.size() == 0 || cvarlang::lang::startsWithComment(line)) continue;
				
				// Check what type the line could be.
				if (cvarlang::lang::isMessageStatement(line)) {
					type = cvarlang::TokenType::Message;
				} else if (cvarlang::lang::startsWithRequire(line)) {
					// Trim the current line if a require is spotted, as if the
					// require keyword is found alone on a line, it can
					// mean a ending of a require block.
					
					// Remove possible comments and whitespace before we do the check.
					
					String trimmed;
					
					if (cvarlang::lang::containsComment(line)) trimmed = line.substr(0, line.find("//"));
					
					utils::trim(line, trimmed);

					// If sub contains a statement, first if statement fails.
					// Meaning that this one must be a start of an require
					// statement, not an end.

					/*
						TODO: add logic to support multiple operators here?
					*/

					if (trimmed.size() == cvarlang::lang::RequireKeyword.size()) {
						type = cvarlang::TokenType::Require;
					} else if (cvarlang::lang::isValidRequire(line)) {
						type = cvarlang::TokenType::Require;
					} else															  {
						pushError(SANI_ERROR_MESSAGE("invalid require statement at line " + std::to_string(i) + ", at file " + file.getFilename()));
					}

					lastRequire = true;
				} else if (cvarlang::lang::isDeclaration(line)) {
					if (cvarlang::lang::isValidDeclaration(line)) {
						type = cvarlang::TokenType::Declaration;
					} else										  {
						pushError(SANI_ERROR_MESSAGE("invalid declaration at line" + std::to_string(i) + ", at file " + file.getFilename()));
					}

					lastRequire = false;
				} else if (cvarlang::lang::isMessageStatement(line)) {
					if (!lastRequire) pushError(SANI_ERROR_MESSAGE("did not except message keyword at this time, at line " + std::to_string(i)));
					
					lastRequire = false;
				} else if (cvarlang::lang::isEmptyOrWhitespace(line)) {
					type = cvarlang::TokenType::EmptyOrComment;

					lastRequire = false;
				} 

				if (type == cvarlang::TokenType::Invalid) {
					// Push error, invalid line.
					pushError(SANI_ERROR_MESSAGE("invalid token at line " + std::to_string(i) + ", at file " + file.getFilename()));
				} else {
					// Should be a valid token.
					tokens.push_back(CVarToken(type, i, file.getFilename(), line));
				}
			}
		}
	}

	CVarTokenizer::~CVarTokenizer()  {
	}
}