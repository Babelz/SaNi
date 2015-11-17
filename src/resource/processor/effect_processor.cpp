#include "sani/resource/processor/effect_processor.hpp"
namespace sani {
	namespace resource {
		namespace processor {

			ResourceItem* EffectProcessor::process(ResourceItem* input) {
				// hmmhhh... 
				// we need to compile and cache the shader, but we
				// cant do it offline
				// TODO how to ^
				return input;
			}
			
		}
	}
}