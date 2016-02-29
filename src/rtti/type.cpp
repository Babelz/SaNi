#include "sani/rtti/type.hpp"
#include "sani/rtti/type_database.hpp"
#include "sani/rtti/field.hpp"
#include "sani/rtti/argument.hpp"
#include <unordered_map>
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

		Object Type::create(Arguments& args) const {
			Signature sig;
			for (auto& arg : args)
				sig.emplace_back(arg.getType());
			auto& ctor = db.types[id].getConstructor(sig);
			return ctor.invoke(args);
		}

		Object Type::createDynamic(Arguments& args) const {
			Signature sig;
			for (auto& arg : args)
				sig.emplace_back(arg.getType());
			auto& ctor = db.types[id].getDynamicConstructor(sig);
			return ctor.invoke(args);
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

		bool Type::isDerivedFrom(const Type other) const {
			auto& base = db.types[id].baseClasses;
			return base.find(other) != base.end();
		}

		const std::vector<Field> Type::getFields() const {
			std::vector<Field> ret;
			auto& fields = db.types[id].fields;
			for (auto& field : fields)
				ret.emplace_back(field.second);
			return ret;
		}

		const Field& Type::getField(const String8& name) const {
			return db.types[id].fields[name];
		}

		const Method& Type::getMethod(const String8& name) const {
			return db.types[id].getMethod(name);
		}

		const std::set<Type>& Type::getBaseClasses() const {
			return db.types[id].baseClasses;
		}

		const std::set<Type>& Type::getDerivedClasses() const {
			return db.types[id].derivedClasses;
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



