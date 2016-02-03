#pragma once

#include "sani/graphics/renderables/particle_emitter.hpp"

namespace sani {

	namespace graphics {

		inline void recomputeVertices(ParticleEmitter& emitter) {
			// Update sprite vertices.
			// Copy vertex data from the particles.
			for (uint32 i = 0; i < emitter.particles.size(); i++) {
				Particle& particle = emitter.particles[i];
				Sprite& sprite = particle.getSprite();

				// Update vertices.
				recomputeVertices(sprite);

				// Extract vertex data.
				const VertexPositionColorTexture* const vertices[] = {
					&sprite.renderData.vertices[0],		// Top-left.
					&sprite.renderData.vertices[1],		// Top-right.
					&sprite.renderData.vertices[2],		// Bottom-left.
					&sprite.renderData.vertices[3]		// Bottom-right.
				};
				
				const float32* const vertexData = reinterpret_cast<const float32* const>(vertices);

				// Copy vertex data from sprite.
			}
		}
		inline void recomputeBounds(ParticleEmitter& emitter) {
			// Compute bounds of the emitter.
			// X = min left
			// W = max right - x
			// Y = min top
			// H = max bottom - y

			// This is an quite costly operation, when the emitter
			// has an initial implementation, pre-compute these values
			// from the particle attributes we get from the user.
		}

		inline void updateRenderData(ParticleEmitter& emitter) {
			// Update sprites render data.
		}

		inline void update(ParticleEmitter& emitter, EngineTime& time) {
			// Update particles.
		}
	}
}