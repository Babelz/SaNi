#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/renderables/particle.hpp"
#include "sani/platform/time/engine_time.hpp"

#include <vector>

namespace sani
{
	namespace graphics
	{
		class ParticleEmitter final : public Renderable {
		public:
			std::vector<Particle> particle;

			ParticleEmitter();
			~ParticleEmitter();
		};

		inline void recomputeVertices(ParticleEmitter& sprite);
		inline void recomputeBounds(ParticleEmitter& sprite);

		inline void updateRenderData(ParticleEmitter& sprite);
		
		inline void update(const EngineTime& time);
	}
}