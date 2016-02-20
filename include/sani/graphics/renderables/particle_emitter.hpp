#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/renderables/particle.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/forward_declare.hpp"
#include "sani/graphics/color.hpp"

#include <functional>
#include <vector>

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

namespace sani {

	namespace graphics {

		class ParticleEmitter;

		using VelocityFunction = std::function<void(Particle&, const ParticleEmitter&, const float32)>;

		void defaultVelocityFunction(Particle& particle, const ParticleEmitter& emitter, const float32 delta);

		/// How the emitter is intended to function.
		enum class EmitFunction {
			/// Emitting particles is stopped when the emitter
			/// is destroyed or when user stops it.
			Continuous,

			/// Emitter will emit particles once and 
			// requires a user called reset.
			Once
		};

		/// How particles should disappear.
		enum class ParticleDecayFunction {
			/// Particles fade before they get decayed.
			Fade,

			/// Particles get hidden/reseted when they decay.
			Disappear
		};

		struct ParticleRenderAttributeList final {
			math::Rect32f source;
		};

		struct ParticleGenerator final {
			std::vector<ParticleRenderAttributeList> attributeLists;

			VelocityFunction velocityFunction;

			math::Vec2f spawnLocationMinOffset;
			math::Vec2f spawnLocationMaxOffset;

			math::Vec2f startVelocity;
			math::Vec2f velocityVariance;

			math::Vec2f baseAcceleration;
			math::Vec2f accelerationVariance;

			math::Vec2f startSize					{ math::Vec2f(32.0f, 32.0f) };
			
			math::Vec2f baseScale					{ math::Vec2f(1.0f, 1.0f) };
			math::Vec2f scaleVariance;

			math::Vec2f baseScaleAcceleration;
			math::Vec2f scaleAccelerationVariance;

			math::Vec2f baseScaleVelocity;
			math::Vec2f scaleVelocityVariance;
			
			Color color								{ color::white };
			Color colorVariance						{ color::white };

			bool varyingSpawnLocation				{ false };
			bool varyingVelocity					{ false };
			bool varyingAcceleration				{ false };
			bool varyingScale						{ false };
			bool varyingScaleAcceleration			{ false };
			bool useScaleAcceleration				{ false };
			bool varyingScaleVelocity				{ false };
			bool useScaleVelocity					{ false };
			bool varyingAngularVelocity				{ false };
			bool varyingAngularAcceleration			{ false };
			bool varyingDecayTime					{ false };
			bool varyingColor						{ false };
			bool varyingAttributes					{ false };

			float32 baseAngularVelocity				{ 0.0f };
			float32 angularVelocityVariance			{ 0.0f };

			float32 baseAngularAcceleration			{ 0.0f };
			float32 angularAccelerationVariance		{ 0.0f };

			float32 baseDecayTime					{ 0.0f };
			float32 decayTimeVariance				{ 0.0f };

			uint32 firstAttributeListIndex			{ 0 };
			uint32 lastAttributeListIndex			{ 0 };
			
			uint32 framesToFade						{ 0 };
			uint32 framesToFadeVariance				{ 0 };
		};

		class ParticleEmitter final : public Renderable {
		public:
			const uint32 maxParticles;

			ParticleDecayFunction particleDecayFunction;
			EmitFunction emitFunction;

			uint32 decayedParticles;
			bool emitting;

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

		inline void resetParticle(const ParticleEmitter& emitter, Particle& particle);
	}
}

#include "sani/graphics/inl/particle_emitter.inl"