#pragma once

#include "sani/engine/services/ecs/component_manager.hpp"
#include "sani/ecs/components/transform_component.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			class TransformManager final : public ComponentManager<Transform> {
			public:
				TransformManager(engine::SaNiEngine* const engine);

				~TransformManager() = default;
			};
		}
	}
}