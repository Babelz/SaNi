#include "sani/graphics/renderables/particle.hpp"

namespace sani {

	using namespace math;
	using namespace resource;

	namespace graphics {

		Particle::Particle(Texture2D* const texute) : timeToLive(0.0f), 
													  angularAcceleration(0.0f),
													  angularVelocity(0.0f),
													  elapsedTime(0.0f),
													  sprite(texute) {
		}
	}
}