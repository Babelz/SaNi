#pragma once

#include "sani/engine/services/updating_renderable_manager.hpp"
#include "sani/graphics/renderables/particle_emitter.hpp"

namespace sani {

	namespace engine {

		namespace services {

			class ParticleEmitterManager final : public UpdatingRenderableManager<graphics::ParticleEmitter> {
			public:
				ParticleEmitterManager(SaNiEngine* const engine); 

				~ParticleEmitterManager() = default;
			};
		}
	}
}