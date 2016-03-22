#pragma once

#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, ResourceItem);

namespace sani {

	namespace resource {

		namespace processor {
			
			class ResourceProcessor {
			public:
				ResourceProcessor() = default;
				~ResourceProcessor() = default;

				virtual ResourceItem* process(ResourceItem* input) = 0;
			};
		}
	}
}

#endif