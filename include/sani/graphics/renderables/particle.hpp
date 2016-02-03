#pragma once

#include "sani/core/math/vector2.hpp"
#include "sani/graphics/renderables/sprite.hpp"
#include "sani/platform/time/engine_time.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsEffect);
SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);
SANI_FORWARD_DECLARE_2(sani, graphics, Transform);

namespace sani {

	using namespace math;
	using namespace resource;

	namespace graphics {

		/// @class Particle particle.hpp "sani/graphics/renderables/particle.hpp"
		/// @author voidbab
		/// 
		/// Class that wraps all particle related information and the sprite 
		/// that serves as the visible part of the particle.
		class Particle final {
		private:
			Vec2f velocity;
			float32 timeToLive;
			float32 angularVelocity;
			
			float32 elapsedTime;

			Sprite sprite;
		public:
			Particle(Texture2D* const texture, const Vec2f& position, const Vec2f& velocity, const float32 angle, 
					 const float32 angularVelocity, const Color& color, const Vec2f& size, const float32 timeToLive);
			
			Particle(Texture2D* const texture);
			
			Sprite& getSprite();
			
			void setVelocity(const Vec2f& velocity);
			void setAngularVelocity(const float32 angularVelocity);
			void setTimeToLive(const float32 time);
			
			/// Returns true if this particle is still alive.
			bool alive() const;
			/// Resets the state of the particle so that it can be used 
			/// again after it has been "marked" as dead.
			void reset(const Vec2f& position);

			/// Updates the particle.
			void update(const EngineTime& time);

			~Particle() = default;
		};
	}
}