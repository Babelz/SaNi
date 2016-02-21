#include "sani/rtti/type.hpp"
#include "sani/rtti/type_database.hpp"

namespace sani {
	namespace rtti {
		namespace { auto &db = TypeDatabase::getInstance(); }

		Type::Type() : id(Type::Invalid) {

		}

		Type::Type(const Type& rhs) 
			: id(rhs.id){

		}

		Type::Type(TypeID id) : id(id) {

		}

		TypeID Type::getID() const {
			return id;
		}

		bool Type::isValid() const {
			return id != Type::Invalid;
		}

		bool Type::isPointer() const {
			return db.types[id].isPointer;
		}

		bool Type::isClass() const {
			return db.types[id].isClass;
		}

		Type::operator bool() const {
			return id != Type::Invalid;
		}

		Object Type::create() const {
			Signature sig;
			auto& ctor = db.types[id].getConstructor(sig);
			return ctor.invoke();
		}

		Object Type::createDynamic() const {
			Signature sig;
			auto& ctor = db.types[id].getDynamicConstructor(sig);
			return ctor.invoke();
		}

		bool Type::operator<(const Type& rhs) const {
			return id < rhs.id;
		}

		bool Type::operator>(const Type& rhs) const {
			return id > rhs.id;
		}

		bool Type::operator>=(const Type& rhs) const {
			return id >= rhs.id;
		}

		bool Type::operator!=(const Type& rhs) const {
			return id != rhs.id;
		}

		bool Type::operator==(const Type& rhs) const {
			return id == rhs.id;
		}

		bool Type::operator<=(const Type& rhs) const {
			return id <= rhs.id;
		}

		Type& Type::operator=(const Type& rhs) {
			id = rhs.id;
			return *this;
		}

	}
}



