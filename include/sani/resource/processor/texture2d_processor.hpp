#pragma once
#include "sani/resource/processor/resource_processor.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/texture2d_content.hpp"
#include <iostream>
namespace sani {
	namespace resource {

		namespace processor {
			class Texture2DProcessorImpl {
			public:
				Texture2DProcessorImpl() = default;
				~Texture2DProcessorImpl() = default;
				Texture2DContent* process(Texture2DContent* input); 
			};
			typedef ResourceProcessor < sani::resource::Texture2DContent, sani::resource::Texture2DContent, Texture2DProcessorImpl > Texture2DProcessor;
		}
	}
}