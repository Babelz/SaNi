#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/transform.hpp"
#include "sani/core/math/vector2.hpp"
#include "sani/core/math/rectangle.hpp"

namespace sani {

	namespace graphics {

		const uint32 ParticleVerticesCount		 = 4;
		const uint32 ParticleIndicesCount		 = 6;
		const uint32 ParticleVertexElementsCount = 9;

		/// @class Particle particle.hpp "sani/graphics/renderables/particle.hpp"
		/// @author voidbab
		/// 
		/// TODO: document
		class Particle final {
		public:
			// Particle vertices.
			VertexPositionColorTexture vertices[ParticleVerticesCount];
			// Transform of particle.
			Transform transform;

			// Global bounds of the particle.
			Rect32f globalBounds;
			// Local bounds of the particle.
			Rect32f localBounds;

			// Velocity of the particle.
			Vec2f velocity;
			
			// Time the particle has until it is being disposed.
			float32 timeToLive;

			// Time elapsed from spawn.
			float32 elapsedTime;

			// Angular velocity of the particle.
			float32 angularVelocity;

			Particle();

			~Particle() = default;
		};

		inline void recomputeVertices(Particle& particle);
		inline void recomputeBounds(Particle& particle);
	}
}

#include "sani/graphics/inl/particle.inl"