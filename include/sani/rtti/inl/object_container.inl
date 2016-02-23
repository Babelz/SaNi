#include "sani/rtti/type_info.hpp"

namespace sani {
	namespace rtti {

		template <class T>
		ObjectContainer<T>::ObjectContainer(const T& value) 
			: value(value) {

		}

		template <class T>
		ObjectContainer<T>::ObjectContainer(const T&& value) 
			: value(std::move(value)) {

		}

		template <class T>
		ObjectBase* ObjectContainer<T>::clone() const {
			return new ObjectContainer<T>(value);
		}

		template <class T>
		Type ObjectContainer<T>::getType() const {
			return Type(TypeInfo<PureType<T> >::id);
		}

		template <class T>
		void* ObjectContainer<T>::getPointer() const {
			return const_cast<void*>(
				reinterpret_cast<const void*>(
					std::addressof(value)
				)
			);
		}
	}
}

