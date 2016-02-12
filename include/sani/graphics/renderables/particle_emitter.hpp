#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/renderables/particle.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/forward_declare.hpp"
#include "sani/graphics/color.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

namespace sani {

	namespace graphics {

		struct ParticleRenderSetup final {
			math::Rect32f source;
		};

		struct ParticleGenerator final {
			math::Vec2f startVelocity;
			math::Vec2f velocityVariance;
			bool varyingVelocity					{ false };

			math::Vec2f startAcceleration;
			math::Vec2f accelerationVariance;
			bool varyingAcceleration;

			math::Vec2f startSize					{ math::Vec2f(32.0f, 32.0f) };
			
			math::Vec2f startScale					{ math::Vec2f(1.0f, 1.0f) };
			math::Vec2f scaleVariance;
			bool varyingScale						{ false };

			math::Vec2f scaleAcceleration;
			math::Vec2f scaleAccelerationVariance;
			bool varyingScaleAcceleration			{ false };
			bool useScaleAcceleration				{ false };

			math::Vec2f scaleVelocity;
			math::Vec2f scaleVelocityVariance;
			bool varyingScaleVelocity				{ false };
			bool useScaleVelocity					{ false };

			float32 startAngularVelocity			{ 0.0f };
			float32 angularVelocityVariance			{ 0.0f };
			bool varyingAngularVelocity				{ false };
			
			float32 startAngularAcceleration		{ 0.0f };
			float32 angularAccelerationVariance		{ 0.0f };
			bool varyingAngularAcceleration			{ false };

			float32 startTimeToLive					{ 0.0f };
			float32 maxTimeToLiveVariance			{ 0.0f };
			bool varyingTimeToLive					{ false };

			Color startColor						{ color::white };
			Color colorVariance						{ color::white };
			bool varyingColor						{ false };

			std::vector<ParticleRenderSetup> setups;
			uint32 firstSetupIndex					{ 0 };
			uint32 lastSetupIndex					{ 0 };
			bool varyingSetup						{ false };
		};

		class ParticleEmitter final : public Renderable {
		public:
			const uint32 maxParticles;

			/// List containing all the particles we are using.
			std::vector<Particle> particles;

			ParticleGenerator generator;

			ParticleEmitter(resource::Texture2D* const texture, const uint32 maxParticles);

			~ParticleEmitter() = default;
		};

		inline void recomputeVertices(ParticleEmitter& emitter);
		inline void recomputeBounds(ParticleEmitter& emitter);

		inline void updateRenderData(ParticleEmitter& emitter);
		
		inline void update(ParticleEmitter& emitter, const EngineTime& time);

		inline void initializeParticles(ParticleEmitter& emitter);

		inline void resetParticle(ParticleEmitter& generator, Particle& particle);
	}
}

#include "sani/graphics/inl/particle_emitter.inl"