#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/transform.hpp"
#include "sani/core/math/vector2.hpp"
#include "sani/platform/time/engine_time.hpp"

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
			VertexPositionColorTexture vertices[ParticleVerticesCount];
			Transform transform;

			Vec2f velocity;
			float32 timeToLive;
			float32 angularVelocity;

			float32 elapsedTime;

			Particle();

			~Particle() = default;
		};
	}
}