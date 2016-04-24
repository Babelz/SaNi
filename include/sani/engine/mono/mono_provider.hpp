#pragma once

#include <mono\jit\jit.h>
#include <mono\metadata\assembly.h>

#include "sani/forward_declare.hpp"

#include "sani/types.hpp"

#include <vector>

SANI_FORWARD_DECLARE_STRUCT(MonoClassDefinition);
SANI_FORWARD_DECLARE_STRUCT(MonoFunctionDefinition);
SANI_FORWARD_DECLARE_STRUCT(MonoFieldDefinition);

namespace sani {

	namespace engine {

		class MonoProvider final {
		private:
			std::vector<MonoAssembly*> assemblies;

			MonoDomain* const monoDomain;
		public:
			MonoProvider(std::vector<MonoAssembly*>& assemblies, MonoDomain* const monoDomain);
			
			MonoClassField* fieldFromDefinition(const MonoClassDefinition* const classDef, const MonoFieldDefinition* const fieldDef) const;
			MonoClass* classFromDefinition(const MonoClassDefinition* const classDef) const;
			MonoType* typeFromDefinition(const MonoClassDefinition* const classDef) const;

			void readField(MonoObject* const instance, const MonoClassDefinition* const classDef, const MonoFieldDefinition* const fieldDef, void* outValue);
			void writeField(MonoObject* const instance, const MonoClassDefinition* const classDef, const MonoFieldDefinition* const fieldDef, void* value);

			bool fieldExists(const MonoClassDefinition* const classDef, const MonoFieldDefinition* const fieldDef);
			bool classExists(const MonoClassDefinition* const classDef) const;
			bool functionExists(const MonoClassDefinition* const classDef, const MonoFunctionDefinition* const funcDef) const;

			void addInternalCall(const MonoClassDefinition* const classDef, const MonoFunctionDefinition* const funcDef) const;

			MonoObject* createObject(const MonoClassDefinition* const classDef) const;
			MonoObject* createObject(const MonoClassDefinition* const classDef, void** args, const uint32 argc) const;

			MonoString* createString(const char* const str) const;

			MonoObject* invoke(MonoString* instance, MonoClass* mclass, const char* const name, void** args, const int32 argc) const;
			MonoObject* invoke(MonoString* instance, MonoClass* mclass, const char* const name) const;

			~MonoProvider() = default;

			MonoProvider& operator =(MonoProvider& other) = delete;
			MonoProvider& operator =(MonoProvider&& other) = delete;

			MonoProvider(MonoProvider& other) = delete;
			MonoProvider(MonoProvider&& other) = delete;
		};
	}
}