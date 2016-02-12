#pragma once

#include "sani/graphics/renderables/particle_emitter.hpp"
#include "sani/core/math/rand.hpp"

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
			for (Particle& particle : emitter.particles) {
				recomputeBounds(particle.sprite);
			}
		}

		void updateRenderData(ParticleEmitter& emitter) {
			for (Particle& particle : emitter.particles) {
				updateRenderData(particle.sprite);
			}

			updateGroupIdentifier(emitter);
		}

		void initializeParticles(ParticleEmitter& emitter) {
			for (Particle& particle : emitter.particles) resetParticle(emitter, particle);
		}

		static void updateAcceleration(Particle& particle, const ParticleGenerator& generator, const float32 delta) {
			particle.acceleration.x += generator.accelerationVariance.x * delta;
			particle.acceleration.y += generator.accelerationVariance.y * delta;
		}
		static void updateAngularAcceleration(Particle& particle, const ParticleGenerator& generator, const float32 delta) {
			particle.angularAcceleration += generator.angularAccelerationVariance * delta;
		}

		static void applyVelocityUpdates(Particle& particle, const float32 delta) {
			particle.angularVelocity += particle.angularAcceleration * delta;
			particle.velocity.x += particle.acceleration.x * delta;
			particle.velocity.y += particle.acceleration.y * delta;
		}
		static void applyPositionUpdates(Particle& particle, const ParticleGenerator& generator, const float32 delta) {
			particle.sprite.transform.rotation += particle.angularVelocity * delta;
			particle.sprite.transform.position.x += particle.velocity.x * delta;
			particle.sprite.transform.position.y += particle.velocity.y * delta;
		}

		void update(ParticleEmitter& emitter, const EngineTime& time) {
			const float32 delta = static_cast<float32>(time.getFrameTime());

			for (Particle& particle : emitter.particles) {
				// Particle is "dead", reset it.
				if (particle.elapsedTime > particle.timeToLive) {
					resetParticle(emitter, particle);

					continue;
				}

				particle.elapsedTime += delta;

				if (emitter.generator.varyingAcceleration)		updateAcceleration(particle, emitter.generator, delta);
				if (emitter.generator.varyingAngularVelocity)	updateAngularAcceleration(particle, emitter.generator, delta);

				applyVelocityUpdates(particle, delta);
				applyPositionUpdates(particle, emitter.generator, delta);

				/*float percent = (static_cast<float>(j) / static_cast<float>(emitter.maxParticles));
				float rad = percent * 2.0f  * 3.14;
				j++;

				sprite.transform.rotation += particle.angularVelocity * frameTime;
				sprite.transform.position.x += particle.velocity.x * cos(rad) * 3.14;
				sprite.transform.position.y += particle.velocity.y * sin(rad) * 3.14;
				*/
			}
		}

		// Static helpers.
		static float32 randomFloat(const float32 min, const float32 max) {
			return rand::nextFloat32(min, max);
		}
		static Vec2f randomVec2(const Vec2f& min, const Vec2f& max) {
			Vec2f randVec2;

			randVec2.x = rand::nextFloat32(min.x, max.x);
			randVec2.y = rand::nextFloat32(min.y, max.y);
			
			return randVec2;
		}
		static Color randomColor(const Color& min, const Color& max) {
			Color randColor;

			randColor.r = rand::nextFloat32(min.r, max.r);
			randColor.g = rand::nextFloat32(min.g, max.g);
			randColor.b = rand::nextFloat32(min.b, max.b);
			randColor.a = rand::nextFloat32(min.a, max.a);

			return randColor;
		}

		inline void resetParticle(ParticleEmitter& emitter, Particle& particle) {
			ParticleGenerator& generator = emitter.generator;
			Sprite& sprite = particle.sprite;
			Transform& transform = sprite.transform;
			
			// Apply new velocity.
			particle.velocity = generator.varyingVelocity ? randomVec2(generator.startVelocity, generator.startVelocity + generator.velocityVariance) :
														   generator.startVelocity;

			// Apply new acceleration.
			particle.acceleration = generator.varyingAcceleration ? randomVec2(generator.startAcceleration, generator.startAcceleration + generator.accelerationVariance) :
																	generator.startAcceleration;

			// Apply new size.
			sprite.localBounds.w = generator.startSize.x;
			sprite.localBounds.h = generator.startSize.y;

			transform.origin.x = sprite.localBounds.w / 2.0f;
			transform.origin.y = sprite.localBounds.h / 2.0f;

			// Apply new scale.
			const Vec2f scale = generator.varyingScale ? randomVec2(generator.startScale, generator.startScale + generator.scaleVariance) :
													     generator.startScale;

			transform.scale.x = scale.x;
			transform.scale.y = scale.y;

			// Apply scale acceleration.

			// Apply scale velocity.

			// Apply new angular velocity.
			particle.angularVelocity = generator.varyingAngularVelocity ? rand::nextFloat32(generator.startAngularVelocity, generator.startAngularVelocity + generator.angularVelocityVariance) :
																		 generator.startAngularVelocity;

			// Apply new angular acceleration.
			particle.angularAcceleration = generator.varyingAngularAcceleration ? rand::nextFloat32(generator.startAngularAcceleration, generator.startAngularAcceleration + generator.angularAccelerationVariance) :
																				  generator.startAngularAcceleration;

			// Apply new time and reset elapsed.
			particle.timeToLive = generator.varyingTimeToLive ?  rand::nextFloat32(generator.startTimeToLive, generator.startTimeToLive + generator.maxTimeToLiveVariance) :
																 generator.startTimeToLive;
			
			sprite.color = generator.varyingColor ? randomColor(generator.startColor, generator.colorVariance) :
												   generator.startColor;

			// Reset state.
			transform.position		= emitter.transform.position;
			transform.position.x	-= sprite.localBounds.w / 2.0f;
			transform.position.y	-= sprite.localBounds.w / 2.0f;
			transform.rotation		= 0.0f;
			particle.elapsedTime	= 0.0f;
		}
	}
}