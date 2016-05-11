#include "sani/graphics/renderables/triangle.hpp"

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

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(triangle)

		using namespace sani::engine::services;
		using namespace sani::graphics;

		static void GetTopPoint(MonoObject* instance, MonoObject* value) {
			Triangle* triangle = mono::getInstance<Triangle>(instance);

			MonoVec2* vec = reinterpret_cast<MonoVec2*>(value);
			vec->x = triangle->topPoint.x;
			vec->y = triangle->topPoint.y;
		}
		static void SetTopPoint(MonoObject* instance, MonoObject value) {
			Triangle* triangle = mono::getInstance<Triangle>(instance);

			MonoVec2* vec = reinterpret_cast<MonoVec2*>(&value);
			triangle->topPoint.x = vec->x;
			triangle->topPoint.y = vec->y;
		}

		static void GetLeftPoint(MonoObject* instance, MonoObject* value) {
			Triangle* triangle = mono::getInstance<Triangle>(instance);

			MonoVec2* vec = reinterpret_cast<MonoVec2*>(value);
			vec->x = triangle->leftPoint.x;
			vec->y = triangle->leftPoint.y;
		}
		static void SetLeftPoint(MonoObject* instance, MonoObject value) {
			Triangle* triangle = mono::getInstance<Triangle>(instance);

			MonoVec2* vec = reinterpret_cast<MonoVec2*>(&value);
			triangle->leftPoint.x = vec->x;
			triangle->leftPoint.y = vec->y;
		}

		static void GetRightPoint(MonoObject* instance, MonoObject* value) {
			Triangle* triangle = mono::getInstance<Triangle>(instance);

			MonoVec2* vec = reinterpret_cast<MonoVec2*>(value);
			vec->x = triangle->rightPoint.x;
			vec->y = triangle->rightPoint.y;
		}
		static void SetRightPoint(MonoObject* instance, MonoObject value) {
			Triangle* triangle = mono::getInstance<Triangle>(instance);

			MonoVec2* vec = reinterpret_cast<MonoVec2*>(&value);
			triangle->rightPoint.x = vec->x;
			triangle->rightPoint.y = vec->y;
		}

		static void Release(MonoObject* instance) {
			Triangle* triangle = getInstance<Triangle>(instance);

			auto* deleteElement = engine->createEmptyMessage<messages::DocumentMessage>();
			deleteElement->setData(triangle);

			renderablemanager::deleteElement(deleteElement, ElementType::Triangle);
			engine->routeMessage(deleteElement);

			engine->releaseMessage(deleteElement);
		}

		static void Instantiate(MonoObject* instance, float32 tx, float32 ty, float32 lx, float32 ly, float32 rx, float32 ry, int32* id, uint32* ptr) {
			auto* createTriangle = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::createElement(createTriangle, ElementType::Triangle);
			engine->routeMessage(createTriangle);

			auto* triangle = static_cast<Triangle*>(createTriangle->getData());

			NEW_DYNAMIC(Triangle, triangle, tx, ty, lx, ly, rx, ry);

			engine->releaseMessage(createTriangle);

			*id = triangle->id;
			*ptr = reinterpret_cast<IntPtr>(triangle);
		}

		static std::vector<Triangle*>* getElements() {
			auto* getElements = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::getElements(getElements, ElementType::Triangle);
			engine->routeMessage(getElements);

			auto elements = static_cast<std::vector<Triangle*>*>(getElements->getData());

			engine->releaseMessage(getElements);

			return elements;
		}

		bool initialize() {
			std::vector<Triangle*>* elements = getElements();

			const MonoClassDefinition classDef("SaNi.Mono.Graphics.Renderables", "Triangle");

			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Instantiate, Instantiate);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Release, Release);

			sani::engine::mono::registerRenderableMembers<Triangle>(elements, classDef);
			sani::engine::mono::registerShapeMembers<Triangle>(elements, classDef);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}