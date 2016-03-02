#include "sani/engine/services/ecs/transform_manager.hpp"

namespace sani {

	namespace engine {

		namespace services {

			TransformManager::TransformManager(engine::SaNiEngine* const engine) 
				: ComponentManager("transform manager", engine) {
			}
		}
	}
}