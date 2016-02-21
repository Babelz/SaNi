#pragma once

#include "sani/rtti/type.hpp"

namespace sani {
	namespace rtti {
		class ObjectBase {
		public:
			/// Returns clone of the object
			virtual ObjectBase* clone() const = 0;
			/// Gets the type of underlaying type
			virtual Type getType() const = 0;
		};
	}
}

