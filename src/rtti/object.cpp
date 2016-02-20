#include "sani/rtti/object.hpp"

namespace sani {
	namespace rtti {

		Object::Object() 
			: _isConst(true), _base(nullptr){

		}

		Object::Object(const Object& rhs) 
			: _isConst(rhs._isConst), _base(rhs._base ? rhs._base->clone() : nullptr) {

		}

		Object::Object(Object&& rhs) 
			: _isConst(rhs._isConst), _base(rhs._base) {
			rhs._isConst = true;
			rhs._base = nullptr;
		}

		Object::~Object() {
			delete _base;
		}

		Type Object::getType() const {
			return _base->getType();
		}

	}
}


