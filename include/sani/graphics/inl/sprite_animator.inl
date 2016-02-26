#pragma once

#include "sani/graphics/renderables/sprite_animator.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/debug.hpp"

namespace sani {
	
	namespace graphics {
		
		void startAnimating(SpriteAnimator& animator) {
			// Check containers.
			SANI_ASSERT(!animator.animations.empty());
			SANI_ASSERT(!animator.sheet.sources.empty());

			changeAnimation(animator, animator.animations.begin()->first);
			
			animator.animating = true;
		}

		bool changeAnimation(SpriteAnimator& animator, const String& name) {
			if (animator.animations.find(name) == animator.animations.end()) return false;
			
			animator.animation = &animator.animations[name];
			animator.animation->currentFrameTime = 0.0f;

			startAnimating(*animator.animation);

			return true;
		}

		void update(SpriteAnimator& animator, const sani::EngineTime& time) {
			if (!animator.animating) return;

			const SpriteAnimationFrame& current = *animator.animation->currentFrame;

			update(*animator.animation, time);

			const SpriteAnimationFrame& next = *animator.animation->currentFrame;
			
			if (next == current) return;

			math::Rect32f source = animator.sheet.sourceAt(current.row, current.column);
			source.x += current.xOffset;
			source.y += current.yOffset;
			source.w += current.widthOffset;
			source.h += current.heightOffset;

			animator.textureSource = source;

			updateRenderData(animator);
		}

		void recomputeVertices(SpriteAnimator& animator) {
			recomputeVertices(static_cast<Sprite&>(animator));
		}
		void recomputeBounds(SpriteAnimator& animator) {
			recomputeBounds(static_cast<Sprite&>(animator));
		}

		void updateRenderData(SpriteAnimator& animator) {
			updateRenderData(static_cast<Sprite&>(animator));
		}
	}
}