#include "sani/graphics/renderables/particle_emitter.hpp"
#include "sani/engine/services/particle_emitter_manager.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			ParticleEmitterManager::ParticleEmitterManager(SaNiEngine* const engine) 
				: RenderableManager("particle emitter manager", ElementType::ParticleEmitter, engine) {
			}

			void ParticleEmitterManager::update(const EngineTime& time) {
				RenderableManager::update(time);

				const RegisterAllocator<graphics::ParticleEmitter>& allocator = getAllocator();
				const std::vector<graphics::ParticleEmitter*>* elements = allocator.allocatedElements();

				auto it = elements->begin();

				while (it != elements->end()) {
					graphics::ParticleEmitter* emitter = *it;

					graphics::update(*emitter, time);

					it++;
				}
			}
		}
	}
}