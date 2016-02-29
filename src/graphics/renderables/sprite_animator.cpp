#include "sani/graphics/renderables/sprite_animator.hpp"

namespace sani {

	namespace graphics {

		SpriteAnimator::SpriteAnimator(Texture* const texture, const float32 x, const float32 y, const float32 w, const float32 h, const uint32 sourceWidth, const uint32 sourceHeight)
			: Sprite(texture, x, y, w, h), animation(nullptr), sheet(SpriteSheet(texture, sourceWidth, sourceHeight)) {
		}
		SpriteAnimator::SpriteAnimator(Texture* const texture, const math::Vec2f& position, const math::Vec2f& size, const uint32 sourceWidth, const uint32 sourceHeight)
			: Sprite(texture, position, size), animation(nullptr), sheet(SpriteSheet(texture, sourceWidth, sourceHeight)) {
		}
		SpriteAnimator::SpriteAnimator(Texture* const texture, const math::Rect32f& bounds, const uint32 sourceWidth, const uint32 sourceHeight)
			: Sprite(texture, bounds), animation(nullptr), sheet(SpriteSheet(texture, sourceWidth, sourceHeight)) {
		}
		SpriteAnimator::SpriteAnimator(Texture* const texture, const math::Vec2f& size, const uint32 sourceWidth, const uint32 sourceHeight)
			: Sprite(texture, size), animation(nullptr), sheet(SpriteSheet(texture, sourceWidth, sourceHeight)) {
		}
		SpriteAnimator::SpriteAnimator(Texture* const texture, const uint32 sourceWidth, const uint32 sourceHeight)
			: Sprite(texture), animation(nullptr), sheet(SpriteSheet(texture, sourceWidth, sourceHeight)) {
		}
	}
}