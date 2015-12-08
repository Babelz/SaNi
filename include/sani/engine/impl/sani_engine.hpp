#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {
		
		template<typename T>
		T* SaNiEngine::allocateShared() {
			return sharedServiceMemory.allocate<T>();
		}

		template<typename T>
		void SaNiEngine::deallocateShared(T* object) {
			sharedServiceMemory.release<T>();
		}
	}
}