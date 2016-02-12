#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/renderables/particle.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/forward_declare.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

namespace sani {

	namespace graphics {

		struct ParticleRenderSetup final {
			resource::Texture2D* texture		{ nullptr };
			math::Rect32f source;

			Color color							{ color::white };
			bool overrideGeneratorColor			{ true };
		};

		struct ParticleGenerator final {
			math::Vec2f minSize					{ math::Vec2f(30.0f, 30.0f) };
			math::Vec2f maxSize					{ math::Vec2f(30.0f, 30.0f) };
			bool randomSize						{ false };

			float32 minAngularVelocity			{ 30.0f };
			float32 maxAngularVelocity			{ 30.0f };
			bool randomAngularVelocity			{ 30.0f };

			float32 minTimeToLive				{ 30.0f };
			float32 maxTimeToLive				{ 30.0f };
			bool randomTimeToLive				{ false };

			Color minColor						{ color::white };
			Color maxColor						{ color::white };
			bool randomColor					{ false };

			std::vector<ParticleRenderSetup> setups;
			uint32 minSetupIndex				{ 0 };
			uint32 maxSetupIndex				{ 0 };
			bool randomSetup					{ false };
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

		inline void resetParticle(Particle& particle);
	}
}

#include "sani/graphics/inl/particle_emitter.inl"