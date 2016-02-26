#include "sani/rtti/method.hpp"

namespace sani {
	namespace rtti {

		Method::Method() 
			: Invokable("INVALID"), _isConst(true), invoker(nullptr), classType(Type::Invalid) {

		}

		Type Method::getClassType() const {
			return classType;
		}

		bool Method::isValid() const {
			return invoker != nullptr;
		}

		bool Method::isConst() const {
			return _isConst;
		}

		Object Method::invoke(Object& instance, Arguments& args) const {
			return invoker(instance, args);
		}

		const Method& Method::invalid() {
			static Method instance;
			return instance;
		}

	}
}