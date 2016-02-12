#pragma once

#include "sani/graphics/renderables/particle_emitter.hpp"
#include "sani/core/math/random.hpp"

namespace sani {

	namespace graphics {

		void recomputeVertices(ParticleEmitter& emitter) {
			uint32 vertexPointer = 0;

			for (Particle& particle : emitter.particles) {
				Sprite& sprite = particle.sprite;

				// Recompute particle vertices.
				recomputeVertices(sprite);

				// Extract vertex data.
				emitter.renderData.vertices[vertexPointer++] = sprite.renderData.vertices[0];
				emitter.renderData.vertices[vertexPointer++] = sprite.renderData.vertices[1];
				emitter.renderData.vertices[vertexPointer++] = sprite.renderData.vertices[2];
				emitter.renderData.vertices[vertexPointer++] = sprite.renderData.vertices[3];
			}
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

		inline void initializeParticles(ParticleEmitter& emitter) {
			for (Particle& particle : emitter.particles) resetParticle(particle);
		}

		void update(ParticleEmitter& emitter, const EngineTime& time) {
			// Do rendering stuff the easy way, just "hide"
			// particles that are not visible so we don't
			// need to recompute the indices etc.

			const float32 frameTime = time.getFrameTime();

			for (Particle& particle : emitter.particles) {
				if (particle.elapsedTime > particle.elapsedTime) {
					resetParticle(particle);

					continue;
				}

				particle.elapsedTime += frameTime;

				Sprite& sprite = particle.sprite;
				
				Vec2f position(sprite.transform.position.x, sprite.transform.position.y);
				position += particle.velocity * frameTime;

				sprite.transform.position = emitter.transform.position;
				sprite.transform.rotation += particle.angularVelocity * frameTime;
				sprite.transform.position.x = position.x;
				sprite.transform.position.y = position.y;
			}
		}

		// Static helpers.
		static float32 randomFloat(const float32 min, const float32 max) {
			return rand::nextFloat32(min, max);
		}
		static Vec2f randomVector2(const Vec2f& min, const Vec2f& max) {
		}

		inline void resetParticle(Particle& particle) {
			
		}
	}
}