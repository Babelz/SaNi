
namespace sani {
	namespace rtti {
		template <class T>
		Object::Object(T& data) 
			: _isConst(std::is_pointer<T>::value && std::is_const<T>::value), 
			_base(new ObjectContainer<PureType<T>>(data)) {

		}
		template <class T>
		Object::Object(T&& data) 
			: _isConst(false), 
			_base(new ObjectContainer<PureType<T>>(static_cast<T&&>(data))) {}

		template <class T>
		Object::Object(T* data) 
			: _isConst(std::is_const<T>::value)  {
			// TODO wrapper for holding pointers
			//static_assert(0);
		}
	}
}

