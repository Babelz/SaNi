#include "sani/rtti/pointer_container.hpp"
#include "sani/rtti/serializable.hpp"

namespace sani {
	namespace rtti {

		PointerContainer::PointerContainer(Serializable* instance) 
			: instance(instance) {
		}

		ObjectBase* PointerContainer::clone() const {
			return new PointerContainer(instance);
		}

		sani::rtti::Type PointerContainer::getType() const {
			return instance->getType();
		}

	}
}


