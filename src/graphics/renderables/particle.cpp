#include "sani/graphics/renderables/particle.hpp"

#include "sani/graphics/graphics_effect.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/graphics/transform.hpp"

namespace sani {

	namespace graphics {

		Particle::Particle(Texture2D* const texture, const Vec2f& position, const Vec2f& velocity, const float32 angle,
						   const float32 angularVelocity, const Color& color, const Vec2f& size, const float32 timeToLive) : velocity(velocity), 
																															 timeToLive(timeToLive), 
																															 angularVelocity(angularVelocity), 
																															 elapsedTime(0),
																															 sprite(texture, position, size) {
		}

		Sprite& Particle::getSprite() {
			return sprite;
		}

		bool Particle::alive() const {
			return elapsedTime < timeToLive;
		}

		void Particle::update(const EngineTime& time) {
			// TODO: add delta to computation.
			const float32 frameTime = time.getFrameTime();
			
			sprite.transform.position.x += velocity.x;
			sprite.transform.position.y += velocity.y;

			sprite.transform.rotation += angularVelocity;
			
			elapsedTime += frameTime;
		}
	}
}