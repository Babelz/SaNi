#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include <vector>

namespace sani
{
	namespace graphics
	{
		class ParticleEmitter final : public Renderable {
		public:
		};

		inline void recomputeVertices(ParticleEmitter& sprite);
		inline void recomputeBounds(ParticleEmitter& sprite);

		inline void updateRenderData(ParticleEmitter& sprite);
	}
}