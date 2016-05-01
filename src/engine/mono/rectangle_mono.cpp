#include "sani/engine/mono/mono_include.hpp"
#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/engine/services/renderable_manager.hpp"
#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/mono/renderable_handler_mono.hpp"
#include "sani/core/memory/memory.hpp"
#include "sani/engine/mono/mono_provider.hpp"

#include "sani/engine/mono/texture2d_mono.hpp"

#include "sani/core/math/rectangle.hpp"
#include "sani/core/math/vector2.hpp"
#include "sani/core/math/vector3.hpp"

#include <mono/metadata/appdomain.h>

#include <iostream>
#include <vector>

#include "sani/types.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(rectangle)

		using namespace sani::engine::services;
		using namespace sani::graphics;

		static void Release(MonoObject* instance, uint32 ptr) {
			Rectangle* rectangle = reinterpret_cast<Rectangle*>(ptr);

			auto* deleteElement = engine->createEmptyMessage<messages::DocumentMessage>();
			deleteElement->setData(rectangle);

			renderablemanager::deleteElement(deleteElement, ElementType::Rectangle);
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

		static std::vector<Rectangle*>* getElements() {
			auto* getElements = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::getElements(getElements, ElementType::Rectangle);
			engine->routeMessage(getElements);

			auto elements = static_cast<std::vector<Rectangle*>*>(getElements->getData());
			
			engine->releaseMessage(getElements);

			return elements;
		}

		bool initialize() {
			std::vector<Rectangle*>* elements = getElements();
			
			const MonoClassDefinition classDef("SaNi.Mono.Graphics.Renderables", "Rectangle");

			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Instantiate, Instantiate);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Release, Release);

			mono::registerRenderableMembers<Rectangle>(elements, classDef);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}