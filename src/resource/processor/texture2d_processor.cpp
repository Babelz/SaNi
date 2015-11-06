#include "sani/resource/processor/texture2d_processor.hpp"
#include <Magick++.h>
#include <sstream>
namespace sani {
	namespace resource {
		namespace processor {
			ResourceItem* Texture2DProcessor::process(ResourceItem* input) {
				using namespace Magick;
				std::cout << "Texture2dProcessor::process() invoked" << std::endl;
				// TODO color keys etc
				Texture2DContent* content = static_cast<Texture2DContent*>(input);
				content->generateMipmaps(false);

				return content;
			}
		}
	}
}