#pragma once

#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/core/cvar/cvar_token.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include <stack>
#include <list>

namespace sani {

	typedef std::stack<String> ErrorBuffer;

	/// @class CVarTokenizer cvar_tokenizer.hpp "sani/core/cvar/cvar_tokenizer.hpp"
	/// @author voidbab
	///
	/// Parse CVar tokens from files.
	class CVarTokenizer {
	private:
		ErrorBuffer errorBuffer;

		void pushError(const String& error);
	public:
		CVarTokenizer();
		
		bool hasErrors() const;
		String getNextError();

		// Creates tokens from given files.
		void tokenize(const std::list<CVarFile*>& files, std::list<CVarToken>& tokens);

		~CVarTokenizer();
	};
}