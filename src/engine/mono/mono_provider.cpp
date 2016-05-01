#include "sani/engine/mono/mono_provider.hpp"
#include "sani/engine/mono/mono_define.hpp"

#include <mono/metadata/class.h>
#include <mono/metadata/metadata.h>
#include <mono/metadata/image.h>
#include <mono/metadata/reflection.h>

#include "sani/types.hpp"

#include <sstream>
#include <cassert>

namespace sani {

	namespace engine {

		namespace mono {

			MonoProvider::MonoProvider(std::vector<MonoAssembly*>& assemblies) : assemblies(assemblies) {
			}

			MonoClass* MonoProvider::classFromDefinition(const MonoClassDefinition* const classDef) const {
				for (auto* monoAssembly : assemblies) {
					MonoImage* image = mono_assembly_get_image(monoAssembly);

					MonoClass* mclass = mono_class_from_name(image, classDef->ns, classDef->name);

					if (mclass != nullptr) return mclass;
				}

				return nullptr;
			}
			MonoType* MonoProvider::typeFromDefinition(const MonoClassDefinition* const classDef) const {
				MonoClass* mclass = classFromDefinition(classDef);

				return mono_class_get_type(mclass);
			}

			MonoObject* MonoProvider::readField(MonoObject* instance, const char* const name) {
				MonoClass* mclass = mono_object_get_class(instance);

				MonoClassField* mfield = mono_class_get_field_from_name(mclass, name);

				MonoObject* value = mono_field_get_value_object(mono_domain_get(), mfield, instance);

				return value;
			}
			void MonoProvider::writeField(MonoObject* instance, const char* const name, void* value) {
				MonoClass* mclass = mono_object_get_class(instance);

				MonoClassField* mfield = mono_class_get_field_from_name(mclass, name);

				mono_field_set_value(instance, mfield, value);
			}

			bool MonoProvider::fieldExists(const MonoClassDefinition* const classDef, const char* const name) {
				return mono_class_get_field_from_name(classFromDefinition(classDef), name) != NULL;
			}
			bool MonoProvider::classExists(const MonoClassDefinition* const classDef) const {
				return classFromDefinition(classDef) != nullptr;
			}
			bool MonoProvider::functionExists(const MonoClassDefinition* const classDef, const MonoFunctionDefinition* const funcDef) const {
				for (auto* monoAssembly : assemblies) {
					MonoImage* image = mono_assembly_get_image(monoAssembly);

					MonoClass* mclass = mono_class_from_name(image, classDef->ns, classDef->name);

					if (mclass == nullptr) continue;

					MonoMethod* method = mono_class_get_method_from_name(mclass, funcDef->name, funcDef->argc);

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

				const String funstr = ss.str();

				mono_add_internal_call(funstr.c_str(), funcDef->ptr);
			}

			MonoObject* MonoProvider::createObject(const MonoClassDefinition* const classDef) const {
				MonoClass* mclass = classFromDefinition(classDef);

				MonoObject* instance = mono_object_new(mono_domain_get(), mclass);

				mono_runtime_object_init(instance);

				return instance;
			}

			MonoObject* MonoProvider::createObject(const MonoClassDefinition* const classDef, void** args, const uint32 argc) const {
				MonoClass* mclass = classFromDefinition(classDef);

				MonoObject* instance = mono_object_new(mono_domain_get(), mclass);
				assert(mono_class_init(mclass));

				MonoMethod* method = nullptr;
				void* iter = nullptr;

				while ((method = mono_class_get_methods(mclass, &iter))) {
					const String name(mono_method_get_name(method));

					if (name == ".ctor") {
						MonoMethodSignature* signature = mono_method_signature(method);

						if (mono_signature_get_param_count(signature) == argc) {
							mono_runtime_invoke(method, instance, args, NULL);

							return instance;
						}
					}
				}

				return nullptr;
			}

			MonoString* MonoProvider::createString(const char* const str) const {
				return mono_string_new(mono_domain_get(), str);
			}

			MonoObject* MonoProvider::invoke(MonoObject* instance, const char* const name, void** args, const int32 argsc) const {
				MonoClass* mclass = mono_object_get_class(instance);

				MonoMethod* method = mono_class_get_method_from_name(mclass, name, argsc);

				return mono_runtime_invoke(method, instance, args, NULL);
			}
			MonoObject* MonoProvider::invoke(MonoObject* instance, const char* const name) const {
				return invoke(instance, name, NULL, NULL);
			}
		}
	}
}