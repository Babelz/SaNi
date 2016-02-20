#pragma once

namespace sani {
	namespace rtti {
		class ObjectBase {
		public:
			/// Returns clone of the object
			virtual ObjectBase* clone() const = 0;
		};
	}
}

