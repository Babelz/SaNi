#pragma once
#include "sani/resource/processor/resource_processor.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/texture2d_content.hpp"
#include <iostream>
namespace sani {
	namespace resource {

		namespace processor {
			class Texture2DProcessor : public ResourceProcessor {
			public:
				Texture2DProcessor() = default;
				~Texture2DProcessor() = default;
				ResourceItem* process(ResourceItem* input) override;
			};
		}
	}
}