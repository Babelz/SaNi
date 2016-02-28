#pragma once

#include <type_traits>

#define typeof(p_type)														   \
	sani::rtti::Type(sani::rtti::TypeInfo<sani::rtti::PureType<p_type> >::id)  \

namespace sani {
	namespace rtti {
		template <class T>
		using PureType = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

		using TypeID = unsigned;
	}
}