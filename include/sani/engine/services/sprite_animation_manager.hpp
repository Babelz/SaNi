#pragma once

#include "sani/engine/services/updating_renderable_manager.hpp"
#include "sani/graphics/renderables/sprite_animator.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			class SpriteAnimationManager final : public UpdatingRenderableManager<graphics::SpriteAnimator> {
			public:
				SpriteAnimationManager(SaNiEngine* const engine);

				~SpriteAnimationManager() = default;
			};
		}
	}
}