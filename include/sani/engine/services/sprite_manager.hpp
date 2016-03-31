#pragma once 

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/graphics/renderables/sprite.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			class SpriteManager final : public RenderableManager<graphics::Sprite> {
			public:
				SpriteManager(SaNiEngine* const engine);
				
				~SpriteManager() = default;
			};
		}
	}
}