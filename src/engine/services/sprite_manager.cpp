#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/services/sprite_manager.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace renderablemanager;
			using namespace graphics;

			SpriteManager::SpriteManager(SaNiEngine* const engine) 
				: RenderableManager("sprite manager", ElementType::Sprite, engine) {
			}
		}
	}
}