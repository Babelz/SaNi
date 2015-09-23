#pragma once

#include "sani/core/cvar/cvar_lang.hpp"

namespace sani {

	/// @class CVarToken cvar_token.hpp "sani/core/cvar/cvar_token.hpp"
	/// @author
	///
	/// Contains compile time information about cvars.
	/// Also used when files are synced.
	class CVarToken {
	private:
		const cvarlang::TokenType type;
		const uint32 lineNumber;
		const String filename;
		const String line;
	public:
		CVarToken(const cvarlang::TokenType type, const uint32 lineNumber, const String& filename, const String& line);

		cvarlang::TokenType getType() const;
		/// Returns the line number of this token.
		uint32 getLineNumber() const;
		/// Returns the filename of this token.
		const String& getFilename() const;
		/// Returns the line.
		const String& getLine() const;

		~CVarToken();
	};
}