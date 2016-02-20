#include "sani/rtti/type_data.hpp"

namespace sani {
	namespace rtti {

		TypeData::TypeData() 
			: isPointer(false), isClass(false) {

		}

		TypeData::TypeData(const String& name) 
			: name(name), isPointer(false), isClass(false) {

		}

	}
}