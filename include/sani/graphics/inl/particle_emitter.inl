#pragma once

#include "sani/graphics/renderables/particle_emitter.hpp"
#include "sani/resource/texture2d.hpp"

namespace sani {

	namespace graphics {

		void recomputeVertices(ParticleEmitter& emitter) {
			// Update sprite vertices.
			// Copy vertex data from the particles.
			uint32 vertexIndex = 0;

			for (uint32 i = 0; i < emitter.particles.size(); i++) {
				Particle& particle = emitter.particles[i];
				Sprite& sprite = particle.getSprite();

				// Update vertices.
				recomputeVertices(sprite);

				// Copy vertex data.
				emitter.renderData.vertices[vertexIndex++] = sprite.renderData.vertices[0];		// Top-left.
				emitter.renderData.vertices[vertexIndex++] = sprite.renderData.vertices[1];		// Top-right.
				emitter.renderData.vertices[vertexIndex++] = sprite.renderData.vertices[2];		// Bottom-left.
				emitter.renderData.vertices[vertexIndex++] = sprite.renderData.vertices[3];		// Bottom-right.
			}
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
			for (Particle& particle : emitter.particles) recomputeBounds(particle.getSprite());

			// Recompute emitter bounds.
		}

		void updateRenderData(ParticleEmitter& emitter) {
			// Update sprites render data.
			for (Particle& particle : emitter.particles) updateRenderData(particle.getSprite());
		}

		void update(ParticleEmitter& emitter, EngineTime& time) {
			// Update particles.
			for (Particle& particle : emitter.particles) particle.update(time);
		}
	}
}