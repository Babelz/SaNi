#include "sani/engine/mono/layers_mono.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(layers)

		static std::vector<MonoObject*> layers;

		static MonoObject* Create(MonoString* name, MonoArray* elements, uint8 type) {
			const MonoClassDefinition classDef("SaNi.Mono.Graphics", "Layer");
			
			const uint32 argc = 2;
			void* args[argc] = {
					name,
					&type
				};

			MonoObject*	layer = MONO_PROVIDER->createObject(&classDef, args, argc);
		
			layers.push_back(layer);

			return layer;
		}

		static void Destroy(MonoObject* layer) {
		}

		static MonoArray* GetLayers() {
			return nullptr;
		}

		bool initialize() {
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Layers, Create, Create);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Layers, Destroy, Destroy);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Layers, GetLayers, GetLayers);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}