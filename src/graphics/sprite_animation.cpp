#include "sani/graphics/sprite_animation.hpp"

namespace sani {

	namespace graphics {

		/*
			Sprite animation frame impl.
		*/
		SpriteAnimationFrame::SpriteAnimationFrame(const uint32 row, const uint32 column) : row(row),
																						    column(column),
																							holdTime(0.0f) {
		}

		/*
			Sprite animation frame group impl.
		*/
		SpriteAnimationFrameGroup::SpriteAnimationFrameGroup(const uint32 firstColumn, const uint32 lastColumn, const uint32 row) {
			for (uint32 i = firstColumn; i < lastColumn; i++) frames.push_back(SpriteAnimationFrame(row, i));
		}

		/*
			Sprite animation impl.
		*/
		SpriteAnimation::SpriteAnimation(const String& name) : name(name),
															   currentFrameTime(currentFrameTime) {
		}
		SpriteAnimation::SpriteAnimation() : SpriteAnimation(String()) {
		}
	}
}