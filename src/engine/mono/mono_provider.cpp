#include "sani/engine/mono/mono_provider.hpp"
#include "sani/engine/mono/mono_define.hpp"

#include <mono/metadata/class.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/image.h>
#include <mono/metadata/reflection.h>

#include "sani/types.hpp"

#include <sstream>

namespace sani {

	namespace engine {

		MonoProvider::MonoProvider(std::vector<MonoAssembly*>& assemblies, MonoDomain* const monoDomain) : assemblies(assemblies),
																										   monoDomain(monoDomain) {
		}

		bool MonoProvider::classExists(const MonoClassDefinition* const classDef) const {
			for (auto* monoAssembly : assemblies) {
				MonoImage* image = mono_assembly_get_image(monoAssembly);

				MonoClass* mclass = mono_class_from_name(image, classDef->ns, classDef->name);
				
				if (mclass != nullptr) return true;
			}

			return false;
		}
		bool MonoProvider::functionExists(const MonoClassDefinition* const classDef, const MonoFunctionDefinition* const funcDef) const {
			for (auto* monoAssembly : assemblies) {
				MonoImage* image = mono_assembly_get_image(monoAssembly);

				MonoClass* mclass = mono_class_from_name(image, classDef->ns, classDef->name);

				if (mclass == nullptr) continue;

				MonoMethod* method = mono_class_get_method_from_name(mclass, funcDef->name, funcDef->argsc);

				if (method != nullptr) return true;
			}

			return false;
		}

		void MonoProvider::addInternalCall(const MonoClassDefinition* const classDef, const MonoFunctionDefinition* const funcDef) const {
			std::stringstream ss;
			ss << classDef->ns;
			ss << ".";
			ss << classDef->name;
			ss << "::";
			ss << funcDef->name;
			ss << (funcDef->argsc == 0 ? "()" : "(" + String(funcDef->signature) + ")");

			auto ringi = ss.str();

			mono_add_internal_call(ringi.c_str(), funcDef->ptr);
		}
	}
}