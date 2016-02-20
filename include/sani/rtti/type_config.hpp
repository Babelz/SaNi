#pragma once

#include <type_traits>


namespace sani {
	namespace rtti {
		template <class T>
		using PureType = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

		using TypeID = unsigned;
	}
}