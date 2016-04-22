#include "sani/engine/mono/resource_manager_mono.hpp"

#include "sani/engine/mono/mono_include.hpp"

#include <functional>
#include <unordered_map>

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(resourcemanager)
	
		using ContentLoader = std::function<MonoObject*(MonoString*)>;
		using ContentLoaderMappings = std::unordered_map<MonoType*, ContentLoader>;

		ContentLoaderMappings mappings;

		static MonoObject* InternalLoad(MonoType* type, MonoString* name) {
			if (mappings.count(type)) return mappings[type](name);

			return nullptr;
		}
		static MonoObject* Load(MonoString* name) {
		}
		static void Unload() {
		}

		static MonoObject* loadTexture2D(MonoString* name) {
			return nullptr;
		}

		static void initializeLoaders() {
			const MonoClassDefinition texture2DDef("SaNi.Mono.Graphics", "Texture2D");

			mappings = ContentLoaderMappings
			{
				{ MONO_PROVIDER->typeFromDefinition(&texture2DDef), loadTexture2D }
			};
		}



		bool initialize() {
			initializeLoaders();

			return false;
		}

		MONO_MODULE_IMPL_END
	}
}