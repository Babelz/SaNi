#pragma once
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, rtti, Type);

namespace sani {
	namespace rtti {
		/// Every serializable object should derive this
		class Reflectable {
		public:
			virtual ~Reflectable() = default;
			virtual Type getType() const = 0;
			virtual Reflectable* clone() const = 0;
		};
	}
}

