#pragma once

#include "sani/graphics/renderables/particle_emitter.hpp"
#include "sani/engine/services/renderable_manager.hpp"

namespace sani {

	namespace engine {

		namespace services {

			class ParticleEmitterManager final : public RenderableManager<graphics::ParticleEmitter> {
			public:
				ParticleEmitterManager(SaNiEngine* const engine);

				virtual void update(const EngineTime& time) override;

				~ParticleEmitterManager() = default;
			};
		}
	}
}