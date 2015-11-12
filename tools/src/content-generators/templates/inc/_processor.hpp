#pragma once
#include "sani/resource/processor/resource_processor.hpp"

namespace sani {
	namespace resource {
		namespace processor {
			class $CLASSNAME : public ResourceProcessor {
			public:
				$CLASSNAME();
				~$CLASSNAME();
				ResourceItem* process(ResourceItem* input) override;
			};
		}
	}
}