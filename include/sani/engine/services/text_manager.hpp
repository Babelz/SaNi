#pragma once

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/graphics/renderables/text.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			class TextManager final : public RenderableManager<graphics::Text> {
			public:
				TextManager(SaNiEngine* const engine);

				~TextManager() = default;
			};
		}
	}
}