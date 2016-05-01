#include "sani/engine/mono/mono_define.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			MonoClassDefinition::MonoClassDefinition(const char* const ns, const char* const name) : ns(ns),
																									 name(name) {
			}
			MonoClassDefinition::MonoClassDefinition() : ns(NULL),
													     name(NULL) {
			}

			MonoClassDefinition MonoClassDefinition::operator = (const MonoClassDefinition& classDef) {
				return MonoClassDefinition(classDef.ns, classDef.name);
			}

			MonoFunctionDefinition::MonoFunctionDefinition(const char* const name, const void* const ptr, const uint32 argc) : name(name),
																															   ptr(ptr),
																															   argc(argc) {
			}
		}
	}
}