#include "sani/rtti/constructor.hpp"

namespace sani {
	namespace rtti {
		Constructor::Constructor() 
			: Invokable("INVALID"), type({ Type::Invalid }), _isDynamic(false), createInstance(nullptr) {

		}

		Constructor::Constructor(Type type, Signature signature, CreateInstance instanceFunc, bool isDynamic) 
			: Invokable("constructor"), type(type), createInstance(instanceFunc), _isDynamic(isDynamic) {
			this->signature = signature;
		}

		bool Constructor::isValid() const {
			return createInstance != nullptr;
		}

		bool Constructor::isDynamic() const {
			return _isDynamic;
		}

		Type Constructor::getType() const {
			return type;
		}

		Object Constructor::invoke() const {
			return createInstance();
		}

		const Constructor& Constructor::invalid(void) {
			static Constructor instance;
			return instance;
		}

	}
}



