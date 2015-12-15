#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/services/circle_manager.hpp"

namespace sani {

	namespace engine {

		namespace services {

			using namespace renderablemanager;
			using namespace graphics;

			CircleManager::CircleManager(SaNiEngine* const engine)
				: RenderableManager("circle manager", ElementType::Triangle, engine) {
			}
		}
	}
}