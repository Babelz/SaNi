#include "sani/rtti/argument.hpp"

namespace sani {
	namespace rtti {

		Argument::Argument() 
			: type({ Type::Invalid }), ptr(nullptr) {

		}

		Argument::Argument(const Argument& rhs) 
			: type(rhs.type), ptr(rhs.ptr) {

		}

		Type Argument::getType() const {
			return type;
		}

		Argument& Argument::operator=(const Argument& rhs) {
			ptr = rhs.ptr;
			const_cast<Type&>(type) = rhs.type;
			return *this;
		}

	}
}

