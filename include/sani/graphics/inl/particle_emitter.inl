#pragma once

#include "sani/graphics/renderables/particle_emitter.hpp"

namespace sani {

	namespace graphics {

		void recomputeVertices(ParticleEmitter& emitter) {
			// Update sprite vertices.
			// Copy vertex data from the particles.
			//uint32 vertexIndex = 0;

			//for (uint32 i = 0; i < emitter.particles.size(); i++) {
			//	Particle& particle = emitter.particles[i];
			//	Sprite& sprite = particle.getSprite();

			//	VertexPositionColorTexture* spriteVertices[] {
			//		&sprite.renderData.vertices[0],		// Top-left.
			//		&sprite.renderData.vertices[1],		// Top-right.
			//		&sprite.renderData.vertices[2],	    // Bottom-left.
			//		&sprite.renderData.vertices[3]		// Bottom-right.
			//	};

			//	const int32 size = 64;

			//	sprite.localBounds.w = size;
			//	sprite.localBounds.h = size;
			//	sprite.transform.position.x = size * i;
			//	sprite.transform.position.y = 0;

			//	// Update vertices.
			//	recomputeVertices(sprite);

			//	// Copy vertex data.
			//	emitter.renderData.vertices[vertexIndex++] = sprite.renderData.vertices[0];		// Top-left.
			//	emitter.renderData.vertices[vertexIndex++] = sprite.renderData.vertices[1];		// Top-right.
			//	emitter.renderData.vertices[vertexIndex++] = sprite.renderData.vertices[2];		// Bottom-left.
			//	emitter.renderData.vertices[vertexIndex++] = sprite.renderData.vertices[3];		// Bottom-right.
			//}
		}
		void recomputeBounds(ParticleEmitter& emitter) {
			// Compute bounds of the emitter.
			// X = min left
			// W = max right - x
			// Y = min top
			// H = max bottom - y

			// This is an quite costly operation, when the emitter
			// has an initial implementation, pre-compute these values
			// from the particle attributes we get from the user.
			//for (Particle& particle : emitter.particles) recomputeBounds(particle.getSprite());

			// Recompute emitter bounds.
			// TODO: recompute emitter bounds.
		}

		void updateRenderData(ParticleEmitter& emitter) {
			// Update sprites render data.
			//emitter.renderData.renderElements[0].texture = emitter.particles[0].getSprite().texture->getID();

			//for (Particle& particle : emitter.particles) updateRenderData(particle.getSprite());
		}

		void update(ParticleEmitter& emitter, const EngineTime& time) {
			// Update particles.
			/*int j = 0; 
			for (auto& p : emitter.particles) {
				p.getSprite().transform.position =
			}*/
			//for (Particle& particle : emitter.particles) particle.update(time);
		}
	}
}