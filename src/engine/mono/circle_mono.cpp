#include "sani/graphics/renderables/circle.hpp"

#include "sani/engine/mono/mono_include.hpp"

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/engine/services/contracts/renderable_manager_contract.hpp"

#include "sani/engine/mono/mono_provider.hpp"

#include "sani/engine/mono/renderable_handler_mono.hpp"
#include "sani/engine/mono/shape_handler_mono.hpp"

#include "sani/core/memory/memory.hpp"

#include <mono/metadata/appdomain.h>

#include <iostream>
#include <vector>

#include "sani/types.hpp"

#include "sani/engine/mono/circle_mono.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(circle)

		using namespace sani::engine::services;
		using namespace sani::graphics;

		static void Instantiate(MonoObject* instance, float32 x, float32 y, float32 radius, uint32 vertices, int32* id, uint32* ptr) {
			auto* createCircle = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::createElement(createCircle, ElementType::Circle);
			engine->routeMessage(createCircle);

			auto* circle = static_cast<Circle*>(createCircle->getData());

			NEW_DYNAMIC(Circle, circle, x, y, radius, vertices);

			engine->releaseMessage(createCircle);

			*id = circle->id;
			*ptr = reinterpret_cast<IntPtr>(circle);
		}
		static void Release(MonoObject* instance) {
			Circle* circle = getInstance<Circle>(instance);

			auto* deleteElement = engine->createEmptyMessage<messages::DocumentMessage>();
			deleteElement->setData(circle);

			renderablemanager::deleteElement(deleteElement, ElementType::Circle);
			engine->routeMessage(deleteElement);

			engine->releaseMessage(deleteElement);
		}

		static void GetRadius(MonoObject* instance, float32* value) {
			Circle* circle = getInstance<Circle>(instance);

			*value = circle->radius;
		}
		static void SetRadius(MonoObject* instance, float32 value) {
			Circle* circle = getInstance<Circle>(instance);

			circle->radius = value;

			recomputeVertices(*circle);
		}

		bool initialize() {
			const MonoClassDefinition classDef("SaNi.Mono.Graphics.Renderables", "Circle");

			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Instantiate, Instantiate);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Release, Release);

			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetRadius, GetRadius);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetRadius, SetRadius);

			sani::engine::mono::registerRenderableMembers<Circle>(classDef);
			sani::engine::mono::registerShapeMembers<Circle>(classDef);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}
