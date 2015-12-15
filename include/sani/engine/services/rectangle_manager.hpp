#pragma once 

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/graphics/renderables/rectangle.hpp"

namespace sani {

	namespace engine {

		namespace services {

			using namespace graphics;

			class RectangleManager : public RenderableManager<Rectangle> {
			public:
				RectangleManager(SaNiEngine* const engine);
			};
		}
	}
}