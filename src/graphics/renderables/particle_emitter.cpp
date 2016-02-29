#include "sani/graphics/renderables/particle_emitter.hpp"

namespace sani {

	using namespace resource;

	namespace graphics {

		void defaultVelocityFunction(Particle& particle, const ParticleEmitter& emitter, const float32 delta) {
			particle.sprite.transform.position.x += particle.velocity.x * delta;
			particle.sprite.transform.position.y += particle.velocity.y * delta;
		}

		ParticleEmitter::ParticleEmitter(Texture2D* const texture, const uint32 maxParticles) 
			: maxParticles(maxParticles), Renderable(maxParticles * ParticleVerticesCount, maxParticles * ParticleVertexElementsCount, 1, texture),
			  emitFunction(EmitFunction::Continuous), decayedParticles(0), emitting(true) {
		
			SANI_ASSERT(texture != nullptr);

			generator.flags = GeneratorFlags::None;

			// Create default setup.
			ParticleRenderAttributeList defaultSetup;
			defaultSetup.source = Rect32f(0.0f, 0.0f, static_cast<float32>(texture->getWidth()), static_cast<float32>(texture->getHeight()));
			
			generator.attributeLists.push_back(defaultSetup);
			generator.velocityFunction = defaultVelocityFunction;

			// Generate particles.
			for (uint32 i = 0; i < maxParticles; i++) {
				particles.push_back(Particle(texture));
			}

			// Generate indices.
			const uint32 indicesCount = maxParticles * ParticleIndicesCount;
			int32 vertexIndexPointer = 0;

			for (uint32 i = 0; i < indicesCount; i += ParticleVerticesCount) {
				renderData.vertexIndices[vertexIndexPointer++] = i;
				renderData.vertexIndices[vertexIndexPointer++] = i + 1;
				renderData.vertexIndices[vertexIndexPointer++] = i + 2;
				
				renderData.vertexIndices[vertexIndexPointer++] = i + 1;
				renderData.vertexIndices[vertexIndexPointer++] = i + 3;
				renderData.vertexIndices[vertexIndexPointer++] = i + 2;
			}

			// Setup render element data.
			RenderElementData& particleRenderData = renderData.renderElements[0];
			particleRenderData.first = 0;
			particleRenderData.last = (maxParticles * ParticleVerticesCount);
			particleRenderData.vertexElements = 9;
			particleRenderData.offset = 0;
			particleRenderData.indices = indicesCount;
			particleRenderData.texture = texture->getID();
			
			renderData.renderElementsCount = 1;
			// No need to compute bounds yet and no need to copy vertex data.
		}
	}
}