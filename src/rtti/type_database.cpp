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
#define REGISTER_TYPE_VARIANTS(type)\
	RTTI_REGISTER_TYPE_VARIANT(type)\
	RTTI_REGISTER_TYPE_VARIANT(type*)\
	RTTI_REGISTER_TYPE_VARIANT(const type*)

		TypeDatabase::TypeDatabase() 
			: types(1), idCounter(1) {
			types[Type::Invalid].name = "INVALID";
			REGISTER_TYPE_VARIANTS(int32);
			REGISTER_TYPE_VARIANTS(float32);
			REGISTER_TYPE_VARIANTS(double);
			REGISTER_TYPE_VARIANTS(void);
			REGISTER_TYPE_VARIANTS(bool);
			REGISTER_TYPE_VARIANTS(String8);
		}
#undef REGISTER_TYPE_VARIANTS
		TypeDatabase::~TypeDatabase() { }

	}
}

