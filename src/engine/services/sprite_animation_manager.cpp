#include "sani/engine/services/sprite_animation_manager.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			SpriteAnimationManager::SpriteAnimationManager(SaNiEngine* const engine)
				: UpdatingRenderableManager("sprite animation manager", ElementType::SpriteAnimation, engine) {
			}
		}
	}
}