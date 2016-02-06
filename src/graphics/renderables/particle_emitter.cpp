#include "sani/graphics/renderables/particle_emitter.hpp"

namespace sani {

	using namespace resource;

	namespace graphics {

		ParticleEmitter::ParticleEmitter(Texture2D* const texture, const uint32 maxParticles) 
			: maxParticles(maxParticles), Renderable(maxParticles * ParticleVerticesCount, maxParticles * ParticleVertexElementsCount, 1, texture) {
		
			SANI_ASSERT(texture != nullptr);

			// Generate particles.
			particles.resize(maxParticles);

			// Generate indices.
			const uint32 indicesCount = maxParticles * ParticleIndicesCount;
			int32 vertexIndexPointer = 0;

			for (uint32 i = 0; i < indicesCount; i += ParticleVerticesCount) {
				renderData.vertexIndices[vertexIndexPointer++] = i;
				renderData.vertexIndices[vertexIndexPointer++] = i + 1;
				renderData.vertexIndices[vertexIndexPointer++] = i + 2;
				
				renderData.vertexIndices[vertexIndexPointer++] = i + 2;
				renderData.vertexIndices[vertexIndexPointer++] = i + 1;
				renderData.vertexIndices[vertexIndexPointer++] = i + 3;
			}

			// Setup render element data.
			RenderElementData& particleRenderData = renderData.renderElements[0];
			particleRenderData.first = 0;
			particleRenderData.last = (maxParticles * ParticleVerticesCount);
			particleRenderData.vertexElements = 9;
			particleRenderData.offset = 0;
			particleRenderData.indices = indicesCount;

			renderData.renderElementsCount = 1;
			// No need to compute bounds yet and no need to copy vertex data.
		}
	}
}