#include "sani/engine/services/particle_emitter_manager.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			ParticleEmitterManager::ParticleEmitterManager(SaNiEngine* const engine)
				: UpdatingRenderableManager("particle emitter manager", ElementType::ParticleEmitter, engine) {
			}
		}
	}
}