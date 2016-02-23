#pragma once 

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/graphics/renderables/circle.hpp"

namespace sani {

	namespace engine {

		namespace services {

			class CircleManager : public RenderableManager<graphics::Circle> {
			public:
				CircleManager(SaNiEngine* const engine);

				~CircleManager() = default;
			};
		}
	}
}