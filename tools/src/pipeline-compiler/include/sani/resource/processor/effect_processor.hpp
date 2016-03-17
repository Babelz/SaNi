#pragma once

#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "sani/resource/processor/resource_processor.hpp"

namespace sani {

	namespace resource {

		namespace processor {

			class EffectProcessor : public ResourceProcessor {
			public:
				ResourceItem* process(ResourceItem* input);
			};
		}
	}
}

#endif