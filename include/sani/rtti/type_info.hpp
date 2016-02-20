#pragma once

#include "sani/rtti/type_config.hpp"
#include "sani/forward_declare.hpp"
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
		};
	}
}

#include "inl/type_info.inl"
