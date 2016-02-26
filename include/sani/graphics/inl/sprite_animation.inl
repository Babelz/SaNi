#pragma once

#include "sani/graphics/sprite_animation.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace graphics {

		void initialize(SpriteAnimation& animation) {
			// Check that we have some frame groups.
			SANI_ASSERT(!animation.frameGroups.empty());
			
			// Check all frame groups before doing anything.
			for (auto frameGroup : animation.frameGroups) SANI_ASSERT(!frameGroup.frames.empty());

			// Initialize.
			animation.currentFrameGroup = animation.frameGroups.begin();	
			animation.currentFrame = animation.currentFrameGroup->frames.begin();
		}

		void update(SpriteAnimation& animation, const sani::EngineTime& time) {
			if (animation.currentFrameTime > animation.currentFrame->holdTime) {
				animation.currentFrameTime = 0.0f;

				animation.currentFrame++;

				// End of group, change group.
				if (animation.currentFrame == animation.currentFrameGroup->frames.end()) {
					
					// Reset or change group.
					if (animation.currentFrameGroup == animation.frameGroups.end()) {
						// Reset back to start.
						animation.currentFrameGroup = animation.frameGroups.begin();
					} else {
						// Swap group.
						animation.currentFrameGroup++;
					}

					animation.currentFrame = animation.currentFrameGroup->frames.begin();
				}
			} else {
				animation.currentFrameTime += time.getFrameTime();
			}
		}
	}
}