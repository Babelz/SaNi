#pragma once 

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/graphics/renderables/triangle.hpp"

namespace sani {

	namespace engine {

		namespace services {

			using namespace graphics;

			class TriangleManager : public RenderableManager<Triangle> {
			public:
				TriangleManager(SaNiEngine* const engine);
			};
		}
	}
}