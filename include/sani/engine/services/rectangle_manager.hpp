#pragma once 

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/graphics/renderables/rectangle.hpp"

namespace sani {

	namespace engine {

		namespace services {

			class RectangleManager final : public RenderableManager<graphics::Rectangle> {
			public:
				RectangleManager(SaNiEngine* const engine);

				~RectangleManager() = default;
			};
		}
	}
}