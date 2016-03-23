#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "sani/resource/processor/scene_description_processor.hpp"
#include "sani/resource/scene.hpp"
#include "sani/rtti/type_database.hpp"
#include "sani/rtti/type.hpp"
#include "sani/debug.hpp"
#include <algorithm>
#include <iostream>

namespace sani {
	namespace resource {
		namespace processor {

			ResourceItem* SceneDescriptionProcessor::process(ResourceItem* input) {
				using namespace rtti;
				auto content = static_cast<SceneDescription*>(input);
                
				return input;
			}

		}
	}
}

#endif



