#pragma once

#include "sani/core/math/vector2.hpp"
#include "sani/graphics/renderables/sprite.hpp"
#include "sani/platform/time/engine_time.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, Texture2D);
SANI_FORWARD_DECLARE_2(sani, graphics, Transform);


namespace sani {

	using namespace sani::math;

	namespace graphics {

		class Particle final {
		private:
			Sprite sprite;
		public:
			Particle();

			void setTexture(Texture2D* const texture);
			void setVelocity(const Vec2f& velocity);
			void setAngle(const float32 angle);
			void setAngularVelocity(const float32 angularVelocity);
			void setSize(const Vec2f& size);
			void setTimeToLive(const float32 timeToLive);

			void update(const EngineTime& time);

			~Particle() = default;
		};
	}
}