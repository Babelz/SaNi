#include "sani/graphics/renderables/rectangle.hpp"

#include "sani/engine/mono/mono_include.hpp"
#include "sani/engine/services/renderable_manager.hpp"
#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/mono/renderable_handler_mono.hpp"
#include "sani/engine/mono/mono_provider.hpp"
#include "sani/engine/mono/shape_handler_mono.hpp"
#include "sani/engine/services/contracts/render_service_contract.hpp"

#include "sani/core/memory/memory.hpp"

#include <mono/metadata/appdomain.h>

#include "sani/graphics/layer.hpp"

#include <iostream>
#include <vector>

#include "sani/types.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(rectangle)

		using namespace sani::engine::services;
		using namespace sani::graphics;

		static void Release(MonoObject* instance) {
			Rectangle* rectangle = getInstance<Rectangle>(instance);

			auto* deleteElement = engine->createEmptyMessage<messages::DocumentMessage>();
			deleteElement->setData(rectangle);

			renderablemanager::deleteElement(deleteElement, ElementType::Rectangle);
			
			// Remove from layer if the element is located inside one.
			uint32 layer = *MONO_UNBOX(MONO_PROVIDER->readField(instance, "layer"), uint32);
			if (layer != NULL) reinterpret_cast<Layer*>(layer)->remove(rectangle);

			engine->routeMessage(deleteElement);
			
			engine->releaseMessage(deleteElement);
		}

		static void Instantiate(MonoObject* instance, float32 x, float32 y, float32 width, float32 height, int32* id, uint32* ptr) {
			auto* createRectangle = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::createElement(createRectangle, ElementType::Rectangle);
			engine->routeMessage(createRectangle);

			auto* rectangle = static_cast<Rectangle*>(createRectangle->getData());

			NEW_DYNAMIC(Rectangle, rectangle, x, y, width, height);

			engine->releaseMessage(createRectangle);

			*id = rectangle->id;
			*ptr = reinterpret_cast<IntPtr>(rectangle);
		}

		bool initialize() {
			const MonoClassDefinition classDef("SaNi.Mono.Graphics.Renderables", "Rectangle");

			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Instantiate, Instantiate);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Release, Release);

			mono::registerRenderableMembers<Rectangle>(classDef);
			mono::registerShapeMembers<Rectangle>(classDef);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}