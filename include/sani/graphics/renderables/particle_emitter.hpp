#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/renderables/particle.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/forward_declare.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

namespace sani {

	namespace graphics {

		class ParticleEmitter final : public Renderable {
		public:
			const uint32 maxParticles;

			/// List containing all the particles we are using.
			std::vector<Particle> particles;

			ParticleEmitter(resource::Texture2D* const texture, const uint32 maxParticles);

			~ParticleEmitter() = default;
		};

		inline void recomputeVertices(ParticleEmitter& emitter);
		inline void recomputeBounds(ParticleEmitter& emitter);

		inline void updateRenderData(ParticleEmitter& emitter);
		
		inline void update(ParticleEmitter& emitter, const EngineTime& time);
	}
}

#include "sani/graphics/inl/particle_emitter.inl"