#pragma once

#include "sani/types.hpp"

namespace sani {
	namespace rtti {
		/// Structure which represents all the data contained within type
		/// constructors, fields, methods
		struct TypeData {
			/// The name of the type
			String8 name;

			/// Constructs invalid type data object
			TypeData();
			/// Constructs valid type data object
			TypeData(const String& name);

			/// Is this pointer type?
			bool isPointer : 1;
			/// Is this class type?
			bool isClass : 1;
			char __padding[2];
		};
		

	}
}

