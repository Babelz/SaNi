#pragma once

#include "sani/core/interfaces/error_logger.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/core/cvar/cvar_token.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include <stack>
#include <list>

namespace sani {

	using namespace interfaces;

	/// @class CVarTokenizer cvar_tokenizer.hpp "sani/core/cvar/cvar_tokenizer.hpp"
	/// @author voidbab
	///
	/// Parse CVar tokens from files.
	class CVarTokenizer final : public ErrorLogger {
	public:
		CVarTokenizer();
		
		// Creates tokens from given files.
		void tokenize(const std::list<CVarFile*>& files, std::list<CVarToken>& tokens);

		~CVarTokenizer();
	};
}