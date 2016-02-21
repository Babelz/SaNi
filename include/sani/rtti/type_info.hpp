#pragma once

#include "sani/rtti/type_config.hpp"
#include "sani/forward_declare.hpp"
#include <type_traits>
SANI_FORWARD_DECLARE_STRUCT_2(sani, rtti, TypeData);

namespace sani {
	namespace rtti {
		/// Helper class for registering and testing if the type is defined
		/// TODO default constructors
		template <class T>
		struct TypeInfo {
			static TypeID id;
			static bool defined;
			static void registerType(TypeID id, TypeData& data, bool defining);

		private:
			template<typename U = T>
			static void addDefaultConstructor(
				TypeData &data,
				typename std::enable_if<
				std::is_trivially_default_constructible<U>::value
				>::type* = nullptr
				);

			
			template<typename U = T>
			static void addDefaultConstructor(
				TypeData &data,
				typename std::enable_if<
				!std::is_trivially_default_constructible<U>::value
				>::type* = nullptr
				);
		};
	}
}

#include "inl/type_info.inl"
