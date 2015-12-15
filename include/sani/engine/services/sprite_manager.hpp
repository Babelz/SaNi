#pragma once 

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/graphics/renderables/sprite.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace graphics;
			
			class SpriteManager : public RenderableManager<Sprite> {
			public:
				SpriteManager(SaNiEngine* const engine);
			};
		}
	}
}