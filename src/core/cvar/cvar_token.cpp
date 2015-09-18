#include "sani/core/cvar/cvar_token.hpp"

namespace sani {

	CVarToken::CVarToken(const cvarlang::TokenType type, const uint32 lineNumber, const String& filename, const String& line) : type(type),
																																lineNumber(lineNumber),
																																filename(filename),
																																line(line) {
	}

	cvarlang::TokenType CVarToken::getType() const {
		return type;
	}
	uint32 CVarToken::getLineNumber() const {
		return lineNumber;
	}
	const String& CVarToken::getFilename() const {
		return filename;
	}
	const String& CVarToken::getLine() const {
		return line;
	}

	CVarToken::~CVarToken() {
	}
}