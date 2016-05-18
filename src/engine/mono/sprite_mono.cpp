#include "sani/graphics/renderables/sprite.hpp"

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

#include "sani/engine/mono/sprite_mono.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(sprite)

		using namespace sani::engine::services;
		using namespace sani::graphics;

		static void Instantiate(MonoObject* instance, float32 x, float32 y, float32 width, float32 height, MonoObject* texture, int32* id, uint32* ptr) {
			auto* createSprite = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::createElement(createSprite, ElementType::Sprite);
			engine->routeMessage(createSprite);

			auto* sprite = static_cast<Sprite*>(createSprite->getData());

			NEW_DYNAMIC(Sprite, sprite, mono::texture2dmonomodule::getNativePtr(texture), x, y, width, height);

			engine->releaseMessage(createSprite);

			*id = sprite->id;
			*ptr = reinterpret_cast<IntPtr>(sprite);
		}
		static void Release(MonoObject* instance) {
			Sprite* sprite = getInstance<Sprite>(instance);

			auto* deleteElement = engine->createEmptyMessage<messages::DocumentMessage>();
			deleteElement->setData(sprite);

			renderablemanager::deleteElement(deleteElement, ElementType::Sprite);
			engine->routeMessage(deleteElement);

			engine->releaseMessage(deleteElement);
		}

		bool initialize() {
			const MonoClassDefinition classDef("SaNi.Mono.Graphics.Renderables", "Sprite");

			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Instantiate, Instantiate);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Release, Release);

			sani::engine::mono::registerRenderableMembers<Sprite>(classDef);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}