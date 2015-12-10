#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {
		
		template <typename T>
		T* const SaNiEngine::createEmptyMessage() {
			T type;

			T* message = static_cast<T*>(createEmptyMessage(type.getType()));
			NEW_DYNAMIC_DEFAULT(T, message);

			return message;
		}

		template<typename T>
		T* SaNiEngine::allocateShared() {
			return sharedServiceMemory.allocate<T>();
		}

		template<typename T>
		void SaNiEngine::deallocateShared(T* memory) {
			sharedServiceMemory.deallocate<T>(memory);
		}
	}
}