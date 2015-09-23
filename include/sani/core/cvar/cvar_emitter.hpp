#include "sani/core/cvar/cvar_token.hpp"
#include "sani/core/cvar/cvar.hpp"
#include <list>

namespace sani {

	namespace cvarlang {

		enum ConditionalOperators {
			// ==
			Equal,

			// !=
			NotEqual,

			// <
			Smaller,

			// <=
			SmallerOrEqual,
			
			// >
			Greater,

			// >=
			GreaterOrEqual
		};
	}

	/// @class CVarEmitter cvar_emitter.hpp "sani/core/cvar/cvar_emitter.hpp"
	/// @author voidbab
	///
	/// Class that is responsible for generating the cvars.
	/// Last step of the compilation.
	class CVarEmitter {
	private:
		struct RequireRecord;
		struct IntermediateCVar;
		struct IntermediateRequire;

	public:
		CVarEmitter();

		void emit(const std::list<CVarToken>& tokens, std::list<CVar>& cvars) const;

		~CVarEmitter();
	};
}