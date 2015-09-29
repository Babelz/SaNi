#pragma once
#include "sani/resource/processor/resource_processor.hpp"
#include "sani/resource/texture2d.hpp"
#include <iostream>
namespace sani {
	namespace resource {

		namespace processor {
			class Texture2DProcessorImpl {
			public:
				Texture2DProcessorImpl() = default;
				~Texture2DProcessorImpl() = default;
				Texture2D* process(Texture2D* input) {
					std::cout << "Texture2DProcessorImpl::load(Texture2D*) invoked" << std::endl;
					return nullptr;
				}
			};
			typedef ResourceProcessor < sani::resource::Texture2D, sani::resource::Texture2D, Texture2DProcessorImpl > Texture2DProcessor;
		}
	}
}