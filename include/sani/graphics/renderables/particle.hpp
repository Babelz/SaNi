#pragma once

#include "sani/core/math/vector2.hpp"
#include "sani/graphics/renderables/sprite.hpp"
#include "sani/platform/time/engine_time.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsEffect);
SANI_FORWARD_DECLARE_2(sani, graphics, Texture2D);
SANI_FORWARD_DECLARE_2(sani, graphics, Transform);

namespace sani {

	using namespace sani::math;

	namespace graphics {

		
		class Particle final {
		private:
			const float32 timeToLive;
			const float32 angularVelocity;
			const Vec2f velocity;

			float32 elapsedTime;

			Sprite sprite;
		public:
			Particle(Texture2D* const texture, const Vec2f& position, const Vec2f& velocity, const float32 angle, 
					 const float32 angularVelocity, const Color& color, const float32 size, const float32 timeToLive);

			Sprite& getSprite();

			void setEffect(GraphicsEffect* const effect);
			
			bool alive() const;

			void update(const EngineTime& time);

			~Particle() = default;
		};
	}
}