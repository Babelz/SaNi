#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include "sani/rtti/type_data.hpp"
#include "sani/rtti/type.hpp"

namespace sani {
	namespace rtti {
		/// This class is mainly used for lookup type data and acts as
		/// helper for querying constructs fields etc.
		class TypeDatabase {
		public:
			/// The lookup map for string => id and vice versa
			std::unordered_map<String8, TypeID> ids;
			/// Contains all the types in the database
			std::vector<TypeData> types;
			
			/// Registers new type to database with name
			/// @returns The id of the type which was created, or Type::Invalid if it already exist
			TypeID registerType(const String& name);

			/// Gets instance
			static TypeDatabase& getInstance();
		private:
			// which id will be assigned to next type
			TypeID idCounter;
			TypeDatabase();
			~TypeDatabase();

		};
	}
}

