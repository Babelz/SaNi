#pragma once
#include "sani/resource/processor/resource_processor.hpp"

namespace sani {
	namespace resource {
		namespace processor {
			class EffectProcessor : public ResourceProcessor {
			public:
				virtual ResourceItem* process(ResourceItem* input) = 0;
			};
		}
	}
}