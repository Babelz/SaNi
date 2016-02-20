#include "sani/rtti/invokable.hpp"

namespace sani {
	namespace rtti {
		Invokable::Invokable(const String8& name)
			: name(name) {

		}

		const Signature& Invokable::getSignature() const {
			return signature;
		}

	}
}

