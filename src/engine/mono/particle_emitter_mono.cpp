#include "sani/engine/services/renderable_manager.hpp"
#include "sani/engine/services/contracts/renderable_manager_contract.hpp"

#include "sani/engine/mono/mono_provider.hpp"

#include "sani/engine/mono/renderable_handler_mono.hpp"

#include "sani/engine/mono/particle_emitter_mono.hpp"

#include "sani/graphics/renderables/particle_emitter.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(particle)

		bool initialize() {
		}

		MONO_MODULE_IMPL_END
	}
}

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(particleemitter)
		
		bool initialize() {
		}

		MONO_MODULE_IMPL_END
	}
}