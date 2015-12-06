#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {
		
		template<typename T>
		T* SaNiEngine::allocateFromSharedMemory() {
			return sharedServiceMemory.allocate<T>();
		}

		template<typename  T>
		void SaNiEngine::releaseFromSharedMemory(T* object) {
			sharedServiceMemory.release<T>();
		}
	}
}