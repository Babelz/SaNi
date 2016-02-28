
namespace sani {
	namespace rtti {
		template <class T>
		Object::Object(T& data)
			: _isConst(std::is_pointer<T>::value && std::is_const<T>::value),
			_base(new ObjectContainer<PureType<T>>(data)) {

		}
		template <class T>
		Object::Object(T&& data,
			typename std::enable_if <!std::is_same<Object&, T>::value>::type*,
			typename std::enable_if<!std::is_const<T>::value>::type*)
			: _isConst(false),
			_base(new ObjectContainer<PureType<T>>(static_cast<T&&>(data))) {}

		template <class T>
		Object::Object(T* data, typename std::enable_if<std::is_base_of<Reflectable, T>::value>::type*)
			: _isConst(std::is_const<T>::value),
			_base(new PointerContainer(
			static_cast<Reflectable*>(const_cast<typename std::remove_const<T>::type*>(data))))
		{

		}

		template <class T>
		T& Object::getValue() const {
			return *static_cast<T*>(_base->getPointer());
		}
	
	}
}

