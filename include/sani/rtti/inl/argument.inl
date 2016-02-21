#pragma once

namespace sani {
	namespace rtti {
		template <class T>
		T& Argument::getValue() const {
			return *reinterpret_cast<typename std::remove_reference<T>::type*>(const_cast<void*>(ptr));
		}

		template <class T>
		Argument::Argument(const T& data)
			: type({ TypeInfo<PureType<T> >::id }),
			ptr(reinterpret_cast<const void*>(std::addressof(data))) {
			static_assert(!std::is_same< Argument, T >::value, "Cannot use Argument as an argument");
		}
	}
}

