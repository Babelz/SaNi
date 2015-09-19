#include "sani/core/cvar/cvar_token.hpp"
#include "sani/core/cvar/cvar.hpp"
#include <list>

namespace sani {

	/// @class CVarEmitter cvar_emitter.hpp "sani/core/cvar/cvar_emitter.hpp"
	/// @author voidbab
	///
	/// Class that is responsible for generating the cvars.
	/// Last step of the compilation.
	class CVarEmitter {
	public:
		CVarEmitter();

		void emit(const std::list<CVarToken>& tokens, std::list<CVar>& cvars) const;

		~CVarEmitter();
	};
}