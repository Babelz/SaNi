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
	}
}

