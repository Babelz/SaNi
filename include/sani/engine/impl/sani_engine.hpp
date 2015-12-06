#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {
		
		template<typename T>
		T* SaNiEngine::allocateFromSharedMemory() {
			sharedServiceMemory->allocate();
		}

		template<typename T>
		void SaNiEngine::releaseFromSharedMemory(T* object) {
			sharedServiceMemory->release();
		}
	}
}