#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/services/triangle_manager.hpp"

namespace sani {

	namespace engine {

		namespace services {

			using namespace renderablemanager;
			using namespace graphics;

			TriangleManager::TriangleManager(SaNiEngine* const engine)
				: RenderableManager("triangle manager", ElementType::Triangle, engine) {
			}
		}
	}
}