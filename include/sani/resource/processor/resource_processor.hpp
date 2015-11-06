#pragma once

namespace sani {
	namespace resource {
		namespace processor {
			
			class ResourceProcessor {
			public:
				~ResourceProcessor() = default;
				virtual void* process(void* input) = 0;
				ResourceProcessor() = default;
			private:
				
			};
		}
	}
}