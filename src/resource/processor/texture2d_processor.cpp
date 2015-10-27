#include "sani/resource/processor/texture2d_processor.hpp"
#include <Magick++.h>
namespace sani {
	namespace resource {
		namespace processor {
			Texture2DContent* Texture2DProcessorImpl::process(Texture2DContent* input) {
				using namespace Magick;
				std::cout << "Texture2dProcessorImpl::process() invoked" << std::endl;
				// TODO color keys etc

				uint32 width = input->width;
				uint32 height = input->height;
				std::vector<Texture2DContent*> mipmapChain;

				Image img;
				img.magick("PNG");
				

				while (width > 1 && height > 1) {
					width /= 2;
					height /= 2;
				}

				return input;
			}
		}
	}
}