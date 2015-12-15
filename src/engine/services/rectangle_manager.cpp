#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/services/rectangle_manager.hpp"

namespace sani {

	namespace engine {

		namespace services {

			using namespace renderablemanager;
			using namespace graphics;

			RectangleManager::RectangleManager(SaNiEngine* const engine)
				: RenderableManager("rectangle manager", ElementType::Triangle, engine) {
			}
		}
	}
}