#pragma once

namespace sani {
	namespace resource {
		namespace processor {
			template <class Input, class Output, class Implementer>
			class ResourceProcessor {
			public:
				~ResourceProcessor() = default;
				Output* process(Input* input) {
					return static_cast<Output*>(impl.process(input));
				}
				ResourceProcessor() = default;
			private:
				Implementer impl;
			};
		}
	}
}