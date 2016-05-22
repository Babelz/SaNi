#include "sani/engine/services/renderable_manager.hpp"
#include "sani/engine/services/contracts/renderable_manager_contract.hpp"

#include "sani/engine/mono/mono_provider.hpp"

#include "sani/engine/mono/renderable_handler_mono.hpp"

#include "sani/engine/mono/particle_emitter_mono.hpp"

#include "sani/graphics/renderables/particle_emitter.hpp"
#include "sani/graphics/renderables/particle.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(particle)

		using namespace sani::engine::services;
		using namespace sani::graphics;

		#define SET_VEC2(__fname__) { \
										auto* p = getInstance<Particle>(instance); \
										p->__fname__.x = value.x; \
										p->__fname__.y = value.y; \
									} \

		#define GET_VEC2(__fname__) { \
										auto* p = getInstance<Particle>(instance); \
										value->x = p->__fname__.x; \
										value->y = p->__fname__.y; \
									} \

		#define GET_VFIELD(__fname__) { \
										auto* p = getInstance<Particle>(instance); \
										*value = p->__fname__; \
									  } \

		
		#define SET_VFIELD(__fname__) { \
										auto* p = getInstance<Particle>(instance); \
										p->__fname__ = value; \
									  } \

		static void SetAcceleration(MonoObject* instance, MonoVec2 value) {
			SET_VEC2(acceleration)
		}
		static void GetAcceleration(MonoObject* instance, MonoVec2* value) {
			GET_VEC2(acceleration)
		}

		static void SetVelocity(MonoObject* instance, MonoVec2 value) {
			SET_VEC2(velocity);
		}
		static void GetVelocity(MonoObject* instance, MonoVec2* value) {
			GET_VEC2(velocity);
		}

		static void SetDecayTime(MonoObject* instance, float32 value) {
			SET_VFIELD(decayTime);
		}
		static void GetDecayTime(MonoObject* instance, float32* value) {
			GET_VFIELD(decayTime);
		}

		static void SetScaleAcceleration(MonoObject* instance, MonoVec2 value) {
			SET_VEC2(scaleAcceleration);
		}
		static void GetScaleAcceleration(MonoObject* instance, MonoVec2* value) {
			GET_VEC2(scaleAcceleration);
		}

		static void GetScaleVelocity(MonoObject* instance, MonoVec2 value) {
			SET_VEC2(scaleVelocity);
		}
		static void SetScaleVelocity(MonoObject* instance, MonoVec2* value) {
			GET_VEC2(scaleVelocity);
		}

		static void GetFrames(MonoObject* instance, uint32* value) {
			GET_VFIELD(frames);
		}

		static void SetFramesBeforeFade(MonoObject* instance, uint32 value) {
			SET_VFIELD(framesBeforeFade);
		}
		static void GetFramesBeforeFade(MonoObject* instance, uint32* value) {
			GET_VFIELD(framesBeforeFade);
		}

		static void SetFadeDelta(MonoObject* instance, float32 value) {
			SET_VFIELD(fadeDelta);
		}
		static void GetFadeDelta(MonoObject* instance, float32* value) {
			GET_VFIELD(fadeDelta);
		}

		static MonoObject* create(const Particle* const particle) {
			uint32 ptr = reinterpret_cast<uint32>(particle);
			
			const uint32 argc = 1;

			void* args[argc] = {
				&ptr
			};

			const MonoClassDefinition classDef("SaNi.Mono.Graphics", "Particle");

			return MONO_PROVIDER->createObject(&classDef, args, argc);
		}

		bool initialize() {
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, GetAcceleration, GetAcceleration);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, SetAcceleration, SetAcceleration);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, GetVelocity, GetVelocity);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, SetVelocity, SetVelocity);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, GetDecayTime, GetDecayTime);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, SetDecayTime, SetDecayTime);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, GetScaleAcceleration, GetScaleAcceleration);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, SetScaleAcceleration, SetScaleAcceleration);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, GetFrames, GetFrames);
			
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, GetFramesBeforeFade, GetFramesBeforeFade);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, SetFramesBeforeFade, SetFramesBeforeFade);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, GetFadeDelta, GetFadeDelta);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Particle, SetFadeDelta, SetFadeDelta);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(particleemitter)
		
		using namespace sani::engine::services;
		using namespace sani::graphics;

		static void Instantiate(float32 x, float32 y, float32 width, float32 height, MonoObject* texture, MonoParticleGenerator generator, int32* id, uint32* ptr) {
		}
		static void Release() {
		}

		static void GetGenerator(MonoParticleGenerator* value) {
		}
		static void SetGenerator(MonoParticleGenerator value) {
		}

		static void GetMaxParticles(int32* value) {
		}

		static MonoArray* GetParticles() {
		}

		static void Reset() {
		}

		bool initialize() {
			const MonoClassDefinition classDef("SaNi.Mono.Graphics", "ParticleEmitter");

			sani::engine::mono::registerRenderableMembers<ParticleEmitter>(classDef);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}