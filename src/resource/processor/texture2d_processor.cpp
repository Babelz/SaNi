#include "sani/resource/processor/texture2d_processor.hpp"
#include <Magick++.h>
#include <sstream>
namespace sani {
	namespace resource {
		namespace processor {
			void* Texture2DProcessor::process(void* input) {
				using namespace Magick;
				std::cout << "Texture2dProcessorImpl::process() invoked" << std::endl;
				// TODO color keys etc
				Texture2DContent* content = static_cast<Texture2DContent*>(input);
				content->generateMipmaps(false);

				return content;
			}
		}
	}
}