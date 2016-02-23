#include "sani/rtti/object_container_standard_types.hpp"

namespace sani {
	namespace rtti {
		ObjectContainer<void>::ObjectContainer() {}
		Type ObjectContainer<void>::getType() const {
			return Type(TypeInfo<void>::id);
		}
		void* ObjectContainer<void>::getPointer() const {
			return nullptr;
		}
		ObjectBase* ObjectContainer<void>::clone() const {
			return new ObjectContainer<void>();
		}

	}
}



