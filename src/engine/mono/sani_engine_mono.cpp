#include "sani/engine/mono/sani_engine_mono.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(saniengine)
		
		static void Exit() {
			engine->exit();
		}

		bool initialize() {
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Engine, SaNiEngine, Exit, Exit);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}