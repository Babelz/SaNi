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

		// Static helpers.
		static void updateVelocity(Particle& particle, const float32 delta) {
			particle.velocity.x += particle.acceleration.x * delta;
			particle.velocity.y += particle.acceleration.y * delta;
		}
		static void updateAngularVelocity(Particle& particle, const float32 delta) {
			particle.angularVelocity += particle.angularAcceleration * delta;
		}
		static void updateScaleVelocity(Particle& particle, const float32 delta) {
			particle.scaleVelocity.x += particle.scaleAcceleration.x * delta;
			particle.scaleVelocity.y += particle.scaleAcceleration.y * delta;
		}
		static void updateFader(Particle& particle, const float32 delta) {
		}

		static void applyVelocity(Particle& particle, const ParticleGenerator& generator, const float32 delta) {
			generator.velocityFunction(particle, generator, delta);
		}
		static void applyAngularVelocity(Particle& particle, const float32 delta) {
			particle.sprite.transform.rotation += particle.angularVelocity * delta;
		}
		static void applyScaleVelocity(Particle& particle, const float32 delta) {
			particle.sprite.transform.scale.x += particle.scaleVelocity.x * delta;
			particle.sprite.transform.scale.y += particle.scaleVelocity.y * delta;
		}

		void update(ParticleEmitter& emitter, const EngineTime& time) {
			const float32 delta = static_cast<float32>(time.getFrameTime());

			for (Particle& particle : emitter.particles) {
				// Particle is "dead", reset it.
				if (particle.elapsedTime > particle.decayTime) {
					resetParticle(emitter, particle);

					continue;
				}

				particle.elapsedTime += delta;

				updateVelocity(particle, delta);
				updateAngularVelocity(particle, delta);
				updateScaleVelocity(particle, delta);
				
				applyVelocity(particle, emitter.generator, delta);
				applyAngularVelocity(particle, delta);
				applyScaleVelocity(particle, delta);

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

		void resetParticle(const ParticleEmitter& emitter, Particle& particle) {
			const ParticleGenerator& generator = emitter.generator;
			Sprite& sprite = particle.sprite;
			Transform& transform = sprite.transform;
			
			// Apply new velocity.
			particle.velocity = generator.varyingVelocity ? randomVec2(generator.startVelocity, generator.startVelocity + generator.velocityVariance) :
														   generator.startVelocity;

			// Apply new acceleration.
			particle.acceleration = generator.varyingAcceleration ? randomVec2(generator.baseAcceleration, generator.baseAcceleration + generator.accelerationVariance) :
																	generator.baseAcceleration;

			// Apply new size.
			sprite.localBounds.w = generator.startSize.x;
			sprite.localBounds.h = generator.startSize.y;

			transform.origin.x = sprite.localBounds.w / 2.0f;
			transform.origin.y = sprite.localBounds.h / 2.0f;

			// Apply new scale.
			const Vec2f scale = generator.varyingScale ? randomVec2(generator.baseScale, generator.baseScale + generator.scaleVariance) :
													     generator.baseScale;

			transform.scale.x = scale.x;
			transform.scale.y = scale.y;

			// Apply scale acceleration.
			Vec2f scaleAcceleration;

			if (generator.useScaleAcceleration) {
				scaleAcceleration = generator.varyingScaleAcceleration ? randomVec2(generator.baseScaleAcceleration, generator.baseScaleAcceleration + generator.scaleAccelerationVariance) :
																		 generator.baseScaleAcceleration;
			}

			particle.scaleAcceleration = scaleAcceleration;

			// Apply scale velocity.
			Vec2f scaleVelocity;

			if (generator.useScaleVelocity) {
				scaleVelocity = generator.varyingScaleVelocity ? randomVec2(generator.baseScaleVelocity, generator.baseScaleVelocity + generator.scaleVelocityVariance) :
																 generator.baseScaleVelocity;
			}

			particle.scaleVelocity = scaleVelocity;

			// Apply new angular velocity.
			particle.angularVelocity = generator.varyingAngularVelocity ? rand::nextFloat32(generator.baseAngularVelocity, generator.baseAngularVelocity + generator.angularVelocityVariance) :
																		 generator.baseAngularVelocity;

			// Apply new angular acceleration.
			particle.angularAcceleration = generator.varyingAngularAcceleration ? rand::nextFloat32(generator.baseAngularAcceleration, generator.baseAngularAcceleration + generator.angularAccelerationVariance) :
																				  generator.baseAngularAcceleration;

			// Apply new time and reset elapsed.
			particle.decayTime = generator.varyingDecayTime ?  rand::nextFloat32(generator.baseDecayTime, generator.baseDecayTime + generator.decayTimeVariance) :
															   generator.baseDecayTime;
			
			sprite.color = generator.varyingColor ? randomColor(generator.color, generator.colorVariance) :
												    generator.color;

			// Apply new setup.
			uint32 attributeListIndex = generator.varyingAttributes ? rand::nextInt32(generator.firstAttributeListIndex, generator.lastAttributeListIndex) :
																	  generator.firstAttributeListIndex;

			const ParticleRenderAttributeList& attributeList = generator.attributeLists[attributeListIndex];

			sprite.textureSource = attributeList.source;

			// Reset position.
			Vec2f positionOffset;

			if (generator.varyingSpawnLocation) {
				positionOffset = randomVec2(generator.spawnLocationMinOffset, generator.spawnLocationMaxOffset);
			}

			transform.position = emitter.transform.position;
			transform.position.x -= (sprite.localBounds.w / 2.0f);
			transform.position.y -= (sprite.localBounds.w / 2.0f);
			transform.position.x += positionOffset.x;
			transform.position.y += positionOffset.y;

			// Reset state.
			transform.rotation		= 0.0f; 

			particle.elapsedTime	= 0.0f;
		}
	}
}