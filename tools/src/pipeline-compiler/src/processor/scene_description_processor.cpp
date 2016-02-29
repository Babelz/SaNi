#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/processor/scene_description_processor.hpp"

namespace sani {
	namespace resource {
		namespace processor {

			ResourceItem* SceneDescriptionProcessor::process(ResourceItem* input) {
				return input;
			}

		}
	}
}

#endif



