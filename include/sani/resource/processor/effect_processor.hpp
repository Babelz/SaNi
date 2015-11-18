#pragma once
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