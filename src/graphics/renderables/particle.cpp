#include "sani/graphics/renderables/particle.hpp"

namespace sani {

	using namespace math;
	
	namespace graphics {

		Particle::Particle() : timeToLive(0.0f), 
							   angularVelocity(0.0f),
							   elapsedTime(0.0f) {
		}
	}
}