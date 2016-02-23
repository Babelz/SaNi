#include "sani/graphics/renderables/particle.hpp"

namespace sani {

	using namespace math;
	using namespace resource;

	namespace graphics {

		Particle::Particle(Texture2D* const texute) : decayTime(0.0f), 
													  angularAcceleration(0.0f),
													  angularVelocity(0.0f),
													  elapsedTime(0.0f),
													  sprite(texute),
													  framesBeforeFade(0),	
													  frames(0),
													  fadeDelta(0.0f) {
		}
	}
}