#pragma once

#include "sani/graphics/renderables/sprite.hpp"

namespace sani {

	namespace graphics {
		
		class SpriteAnimator final : public Sprite {
		public:
			SpriteAnimator(resource::Texture2D* const texture, const float32 x, const float32 y, const float32 w, const float32 h);
			SpriteAnimator(resource::Texture2D* const texture, const math::Vec2f& position, const math::Vec2f& size);
			SpriteAnimator(resource::Texture2D* const texture, const math::Rect32f& bounds);
			SpriteAnimator(resource::Texture2D* const texture, const math::Vec2f& size);
			SpriteAnimator(resource::Texture2D* const texture);

			~SpriteAnimator() = default;
		};
	}
}