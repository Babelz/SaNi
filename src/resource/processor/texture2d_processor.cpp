#include "sani/resource/processor/texture2d_processor.hpp"
#include <Magick++.h>
#include <sstream>
namespace sani {
	namespace resource {
		namespace processor {
			Texture2DContent* Texture2DProcessorImpl::process(Texture2DContent* input) {
				using namespace Magick;
				std::cout << "Texture2dProcessorImpl::process() invoked" << std::endl;
				// TODO color keys etc

				input->generateMipmaps(false);

				return input;
			}
		}
	}
}