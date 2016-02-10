#pragma once

#include "sani/graphics/renderables/particle_emitter.hpp"

namespace sani {

	namespace graphics {

		void recomputeVertices(ParticleEmitter& emitter) {
			#pragma region 
			// Update particle data.
			//for (Particle& particle : emitter.particles) recomputeVertices(particle);
			#pragma endregion

		}
		void recomputeBounds(ParticleEmitter& emitter) {
			#pragma region 
			// This is an quite costly operation, when the emitter
			// has an initial implementation, pre-compute these values
			// from the particle attributes we get from the user?

			// Update particle bounds and find max x and y.
			//float32 right = 0.0f;
			//float32 bottom = 0.0f;

			//for (Particle& particle : emitter.particles) {
			//	recomputeBounds(particle);
			//	
			//	if (particle.globalBounds.right() > right)		right = particle.globalBounds.right();
			//	if (particle.globalBounds.bottom() > bottom)	bottom = particle.globalBounds.bottom();
			//}

			//// Find min x and y.
			//float32 x = right;
			//float32 y = bottom;

			//for (Particle& particle : emitter.particles) {
			//	if (particle.globalBounds.left() < x)	x = particle.globalBounds.left();
			//	if (particle.globalBounds.top() < y)	y = particle.globalBounds.top();
			//}

			//emitter.globalBounds.x = x;
			//emitter.globalBounds.y = y;
			//emitter.globalBounds.w = right - x;
			//emitter.globalBounds.h = bottom - y;
			#pragma endregion

		}

		void updateRenderData(ParticleEmitter& emitter) {
			#pragma region 
			// Update sprites render data.
			//emitter.renderData.renderElements[0].texture = emitter.texture->getID();

			//if (!emitter.textureSource.isEmpty()) {
			//	for (Particle& particle : emitter.particles) {
			//		// TODO: sourcing...
			//	}
			//} else {
			//	for (Particle& particle : emitter.particles) {
			//		VertexPositionColorTexture* vertices[] {
			//			&particle.vertices[0],
			//			&particle.vertices[1],
			//			&particle.vertices[2],
			//			&particle.vertices[3]
			//		};

			//		applyDefaultRectangleTextureCoordinates(vertices);
			//	}
			//}

			//updateGroupIdentifier(emitter);
			#pragma endregion

		}

		void update(ParticleEmitter& emitter, const EngineTime& time) {
			#pragma region 
			// Update particles.
			/*int j = 0; 
			for (auto& p : emitter.particles) {
				p.getSprite().transform.position =
			}*/
			//for (Particle& particle : emitter.particles) particle.update(time);
			#pragma endregion

		}
	}
}