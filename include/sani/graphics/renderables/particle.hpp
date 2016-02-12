#pragma once

#include "sani/core/math/vector2.hpp"
#include "sani/core/math/rectangle.hpp"
#include "sani/graphics/renderables/sprite.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

namespace sani {

	namespace graphics {

		const uint32 ParticleVerticesCount		 = 4;
		const uint32 ParticleIndicesCount		 = 6;
		const uint32 ParticleVertexElementsCount = 9;

		/// @class Particle particle.hpp "sani/graphics/renderables/particle.hpp"
		/// @author voidbab
		/// 
		/// Represents a single particle.
		class Particle final {
		public:
			// Sprite of the particle.
			Sprite sprite;

			Vec2f acceleration;
			Vec2f velocity;
			
			// Time the particle has until it is being disposed.
			float32 timeToLive;

			// Time elapsed from spawn.
			float32 elapsedTime;

			// Angular velocity of the particle.
			float32 angularAcceleration;
			float32 angularVelocity;

			Vec2f scaleAcceleration;
			Vec2f scaleVelocity;

			Particle(resource::Texture2D* const texture);

			~Particle() = default;
		};
	}
}