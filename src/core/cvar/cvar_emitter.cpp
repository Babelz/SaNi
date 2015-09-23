#include "sani/core/cvar/cvar_emitter.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include <sstream>

namespace sani {

	struct RequireRecord {
		std::function<bool(void)> Func;
		uint32 Scope;
	};

	CVarEmitter::CVarEmitter() {
	}

	CVarEmitter::~CVarEmitter() {
	}
}