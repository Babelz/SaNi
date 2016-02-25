#include "sani/rtti/field.hpp"

namespace sani {
	namespace rtti {

		Field::Field() 
			: type(Type::Invalid), classType(Type::Invalid), 
			  getter(nullptr), setter(nullptr) {

		}

		Field::Field(const String8& name, Type type, Type classType, Getter getter, Setter setter)
			: name(name), type(type), classType(classType), getter(getter), setter(setter) {

		}

		bool Field::isValid() const {
			return getter != nullptr;
		}

		bool Field::isReadOnly() const {
			return setter == nullptr;
		}

		sani::rtti::Type Field::getType() const	{
			return type;
		}

		sani::rtti::Type Field::getClassType() const {
			return classType;
		}

		const String8& Field::getName() const {
			return name;
		}

		Object Field::getValue(Object& instance) const {
			return getter(instance);
		}

		bool Field::setValue(Object& instance, const Object& newValue) const {
			if (setter && !instance.isConst()) {
				setter(instance, newValue);
				return true;
			}
			return false;
		}

	}
}



