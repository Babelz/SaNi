#pragma once 

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/graphics/renderables/circle.hpp"

namespace sani {

	namespace engine {

		namespace services {

			using namespace graphics;

			class CircleManager : public RenderableManager<Circle> {
			public:
				CircleManager(SaNiEngine* const engine);
			};
		}
	}
}