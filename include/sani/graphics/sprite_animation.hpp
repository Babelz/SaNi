#pragma once

#include "sani/platform/time/engine_time.hpp"
#include "sani/types.hpp"

#include <vector>

namespace sani {

	namespace graphics {

		/*
			TODO: load from content?
		*/

		/// @class SpriteAnimationFrame sprite_animation.hpp "sani/graphics/sprite_animation.hpp"
		/// @author voidbab
		/// 
		/// One frame of the sprite animation.
		/// Each frame can have different
		/// hold time.
		class SpriteAnimationFrame final {
		public:
			uint32 row;
			uint32 column;

			// Time this frame is being presented to the user
			// before moving to the next frame.
			float32 holdTime;

			SpriteAnimationFrame(const uint32 row, const uint32 column);

			~SpriteAnimationFrame() = default;
		};

		/// @class SpriteAnimationFrameGroup sprite_animation.hpp "sani/graphics/sprite_animation.hpp"
		/// @author voidbab
		/// 
		/// Defines a frame group for part of the animation.
		/// One animation can contain more than one frame group.
		class SpriteAnimationFrameGroup final {
		public:
			std::vector<SpriteAnimationFrame> frames;

			SpriteAnimationFrameGroup(const uint32 firstColumn, const uint32 lastColumn, const uint32 row);
			
			~SpriteAnimationFrameGroup() = default;
		};

		using FrameGroupIterator	= std::vector<SpriteAnimationFrameGroup>::iterator;
		using FrameIterator			= std::vector<SpriteAnimationFrame>::iterator;


		/// @class SpriteAnimation sprite_animation.hpp "sani/graphics/sprite_animation.hpp"
		/// @author voidbab
		/// 
		/// Sprite animation that can contain one or more frame groups.
		/// Animation will execute all frame groups before it is marked
		/// as finished.
		class SpriteAnimation final {
		public:
			std::vector<SpriteAnimationFrameGroup> frameGroups;
			FrameGroupIterator currentFrameGroup;				// Frame group that is being executed.
			FrameIterator currentFrame;						   // Current frame of the current frame group.

			/// Current frames time.
			float32 currentFrameTime;

			SpriteAnimation();

			~SpriteAnimation() = default;
		};

		/// Initializes the animation, should be called once all
		/// frame groups have been created.
		inline void startAnimating(SpriteAnimation& animation);

		inline void update(SpriteAnimation& animation, const sani::EngineTime& time);
	}
}

#include "sani/graphics/inl/sprite_animation.inl"