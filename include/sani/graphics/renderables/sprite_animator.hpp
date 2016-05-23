#pragma once

#include "sani/platform/time/engine_time.hpp"
#include "sani/graphics/renderables/sprite.hpp"
#include "sani/graphics/sprite_animation.hpp"
#include "sani/graphics/sprite_sheet.hpp"

#include <unordered_map>

namespace sani {

	namespace graphics {
		
		class SpriteAnimator final : public Sprite {
		public:
			std::unordered_map<String, SpriteAnimation> animations;

			SpriteAnimation* animation;
			SpriteSheet sheet;

			bool animating;

			SpriteAnimator(Texture* const texture, const float32 x, const float32 y, const float32 w, const float32 h, const uint32 sourceWidth, const uint32 sourceHeight);
			SpriteAnimator(Texture* const texture, const math::Vec2f& position, const math::Vec2f& size, const uint32 sourceWidth, const uint32 sourceHeight);
			SpriteAnimator(Texture* const texture, const math::Rect32f& bounds, const uint32 sourceWidth, const uint32 sourceHeight);
			SpriteAnimator(Texture* const texture, const math::Vec2f& size, const uint32 sourceWidth, const uint32 sourceHeight);
			SpriteAnimator(Texture* const texture, const uint32 sourceWidth, const uint32 sourceHeight);

			~SpriteAnimator() = default;
		};

		inline void startAnimating(SpriteAnimator& animator);

		inline bool changeAnimation(SpriteAnimator& animator, const String& name);

		inline void update(SpriteAnimator* animator, const sani::EngineTime& time);
		
		inline void recomputeVertices(SpriteAnimator& animator);
		inline void recomputeBounds(SpriteAnimator& animator);

		inline void updateRenderData(SpriteAnimator& animator);
	}
}

#include "sani/graphics/inl/sprite_animator.inl"