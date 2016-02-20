#include "sani/rtti/type_database.hpp"
#include <algorithm>
#include "sani/preprocessor/rtti_runtime.hpp"

namespace sani {
	namespace rtti {

		TypeID TypeDatabase::registerType(const String& name) {
			// its defined already, return invalid
			if (ids.find(name) != ids.end()) return Type::Invalid;
			
			types.emplace_back(name);
			// create new id and assign it to name
			auto id = idCounter++;
			ids[name] = id;
			return id;
		}

		TypeDatabase& TypeDatabase::getInstance() {
			static TypeDatabase instance;
			return instance;
		}

		TypeDatabase::TypeDatabase() 
			: types(1), idCounter(1) {
			types[Type::Invalid].name = "INVALID";
			RTTI_REGISTER_TYPE(int32);
			RTTI_REGISTER_TYPE(float32);
			RTTI_REGISTER_TYPE(double);
			RTTI_REGISTER_TYPE(void);
			RTTI_REGISTER_TYPE(bool);
			RTTI_REGISTER_TYPE(String8);
		}

		TypeDatabase::~TypeDatabase() { }

	}
}

