#include "sani/engine/services/renderable_manager.hpp"
#include "sani/engine/services/contracts/renderable_manager_contract.hpp"

#include "sani/engine/mono/mono_provider.hpp"

#include "sani/engine/mono/renderable_handler_mono.hpp"

#include "sani/engine/mono/particle_emitter_mono.hpp"

#include "sani/graphics/renderables/particle_emitter.hpp"
#include "sani/graphics/renderables/particle.hpp"

#include "sani/graphics/layer.hpp"

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

		#define GET_FIELD(__fname__) { \
										auto* p = getInstance<Particle>(instance); \
										*value = p->__fname__; \
									  } \

		
		#define SET_FIELD(__fname__) { \
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
			SET_FIELD(decayTime);
		}
		static void GetDecayTime(MonoObject* instance, float32* value) {
			GET_FIELD(decayTime);
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
			GET_FIELD(frames);
		}

		static void SetFramesBeforeFade(MonoObject* instance, uint32 value) {
			SET_FIELD(framesBeforeFade);
		}
		static void GetFramesBeforeFade(MonoObject* instance, uint32* value) {
			GET_FIELD(framesBeforeFade);
		}

		static void SetFadeDelta(MonoObject* instance, float32 value) {
			SET_FIELD(fadeDelta);
		}
		static void GetFadeDelta(MonoObject* instance, float32* value) {
			GET_FIELD(fadeDelta);
		}

		static MonoObject* create(const Particle* const particle) {
			uint32 ptr = reinterpret_cast<uint32>(particle);
			
			const uint32 argc = 1;

			void* args[argc] = {
				&ptr
			};

			const MonoClassDefinition classDef("SaNi.Mono.Graphics.Renderables", "Particle");

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

		static void Instantiate(MonoObject* instance, float32 x, float32 y, float32 width, float32 height, MonoObject* texture, MonoParticleGenerator generator, uint32 maxParticles, int32* id, uint32* ptr) {
			auto* createEmitter = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::createElement(createEmitter, ElementType::ParticleEmitter);
			engine->routeMessage(createEmitter);

			auto* emitter = static_cast<ParticleEmitter*>(createEmitter->getData());

			NEW_DYNAMIC(ParticleEmitter, emitter, texture2dmonomodule::getNativePtr(texture), maxParticles);
			emitter->transform.position.x = x;
			emitter->transform.position.y = y;
			emitter->localBounds.w = width;
			emitter->localBounds.h = height;

			// Copy data.
			std::memcpy(&emitter->generator, &generator, sizeof(MonoParticleGenerator));

			engine->releaseMessage(createEmitter);

			*id = emitter->id;
			*ptr = reinterpret_cast<IntPtr>(emitter);

			initializeParticles(*emitter);
		}
		static void Release(MonoObject* instance) {
			ParticleEmitter* emitter = getInstance<ParticleEmitter>(instance);

			auto* deleteElement = engine->createEmptyMessage<messages::DocumentMessage>();
			deleteElement->setData(emitter);

			renderablemanager::deleteElement(deleteElement, ElementType::ParticleEmitter);

			// Remove from layer if the element is located inside one.
			uint32 layer = *MONO_UNBOX(MONO_PROVIDER->readField(instance, "layer"), uint32);
			if (layer != NULL) reinterpret_cast<Layer*>(layer)->remove(emitter);

			engine->routeMessage(deleteElement);

			engine->releaseMessage(deleteElement);
		}

		static void GetGenerator(MonoObject* instance, MonoParticleGenerator* value) {
			ParticleEmitter* emitter = getInstance<ParticleEmitter>(instance);

			std::memcpy(value, &emitter->generator, sizeof(MonoParticleGenerator));
		}
		static void SetGenerator(MonoObject* instance, MonoParticleGenerator value) {
			ParticleEmitter* emitter = getInstance<ParticleEmitter>(instance);

			std::memcpy(&emitter->generator, &value, sizeof(MonoParticleGenerator));
		
			initializeParticles(*emitter);
		}

		static void GetMaxParticles(MonoObject* instance, int32* value) {
			ParticleEmitter* emitter = getInstance<ParticleEmitter>(instance);

			*value = emitter->maxParticles;
		}

		static MonoArray* GetParticles(MonoObject* instance) {
			ParticleEmitter* emitter = getInstance<ParticleEmitter>(instance);

			const uint32 arraySize = emitter->particles.size();
			
			MonoClassDefinition particleClass("SaNi.Mono.Graphics.Renderables", "Particle");

			MonoArray* particles = MONO_PROVIDER->createArray(&particleClass, arraySize);
			
			for (uint32 i = 0; i < arraySize; i++) {
				const uint32 argc = 1;

				uint32 ptr = reinterpret_cast<IntPtr>(&emitter->particles[i]);

				void* args[argc] = {
					&ptr
				};

				MonoObject* particle = MONO_PROVIDER->createObject(&particleClass, args, argc);
				
				mono_array_set(particles, MonoObject*, i, particle);
			}

			return particles;
		}

		static void Reset(MonoObject* instance) {
			ParticleEmitter* emitter = getInstance<ParticleEmitter>(instance);

			initializeParticles(*emitter);
		}

		bool initialize() {
			const MonoClassDefinition classDef("SaNi.Mono.Graphics.Renderables", "ParticleEmitter");

			sani::engine::mono::registerRenderableMembers<ParticleEmitter>(classDef);

			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Instantiate, Instantiate);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Release, Release);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, Reset, Reset);

			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetGenerator, GetGenerator);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetGenerator, SetGenerator);

			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetMaxParticles, GetMaxParticles);
			MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetParticles, GetParticles);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}