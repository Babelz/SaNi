#include "sani/rtti/pointer_container.hpp"
#include "sani/rtti/Reflectable.hpp"

namespace sani {
	namespace rtti {

		PointerContainer::PointerContainer(Reflectable* instance) 
			: instance(instance) {
		}

		ObjectBase* PointerContainer::clone() const {
			return new PointerContainer(instance);
		}

		sani::rtti::Type PointerContainer::getType() const {
			return instance->getType();
		}

		void* PointerContainer::getPointer() const {
			return instance;
		}

	}
}


