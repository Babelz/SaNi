#pragma once

#include <mono\jit\jit.h>
#include <mono\metadata\assembly.h>

#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_STRUCT(MonoClassDefinition);
SANI_FORWARD_DECLARE_STRUCT(MonoFunctionDefinition);

namespace sani {

	namespace engine {

		class MonoProvider final {
		private:
			MonoAssembly* const monoAssembly;
			MonoDomain* const monoDomain;
		public:
			MonoProvider(MonoAssembly* const monoAssembly, MonoDomain* const monoDomain);
			
			bool classExists(const MonoClassDefinition* const classDef) const;
			bool functionExists(const MonoClassDefinition* const classDef, const MonoFunctionDefinition* const funcDef) const;

			void addInternalCall(const MonoClassDefinition* const classDef, const MonoFunctionDefinition* const funcDef) const;

			~MonoProvider() = default;

			MonoProvider& operator =(MonoProvider& other) = delete;
			MonoProvider& operator =(MonoProvider&& other) = delete;

			MonoProvider(MonoProvider& other) = delete;
			MonoProvider(MonoProvider&& other) = delete;
		};
	}
}