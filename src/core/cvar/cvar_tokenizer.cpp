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
				}
				else if (cvarlang::lang::startsWithRequire(line)) {
					if (cvarlang::lang::isValidRequire(line)) type = cvarlang::TokenType::Require;
				}
				else if (cvarlang::lang::isDeclaration(line)) {
					if (cvarlang::lang::isValidDeclaration(line)) type = cvarlang::TokenType::Declaration;
				}

				// Check for errors.
				if (type == cvarlang::TokenType::Invalid) {
					String error("");//(SANI_ERROR_MESSAGE("cvar syntax error at line " + std::to_string(i)));

					//pushError(error);
				}
			}
		}
	}

	CVarTokenizer::~CVarTokenizer()  {
	}
}