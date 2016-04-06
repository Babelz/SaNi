#include "sani/engine/mono/mono_provider.hpp"
#include "sani/engine/mono/mono_define.hpp"

namespace sani {

	namespace engine {

		MonoProvider::MonoProvider(MonoAssembly* const monoAssembly, MonoDomain* const monoDomain) : monoAssembly(monoAssembly),
																									 monoDomain(monoDomain) {
		}

		bool MonoProvider::classExists(const MonoClassDefinition* const classDef) const {
			return true;
		}
		bool MonoProvider::functionExists(const MonoClassDefinition* const classDef, const MonoFunctionDefinition* const funcDef) const {
			return true;
		}

		void MonoProvider::addInternalCall(const MonoClassDefinition* const classDef, const MonoFunctionDefinition* const funcDef) const {
		}
	}
}