#pragma once
#include <vector>
#include "sani/rtti/type_config.hpp"

namespace sani {
	namespace rtti {
		/// Class that represents type in RTTI
		class Type {
		public:
			using List = std::vector<Type>;
			static const TypeID Invalid = 0;
			/// Constructs new invalid type
			Type();
			/// Constructs copy of the type
			Type(const Type& rhs);
			/// Constructs new type 
			Type(TypeID id);

			/// Gets the internal id of the type which can be used to query data from database
			TypeID getId() const;

			/// Checks if the type is valid
			bool isValid() const;

			/// Checks if the type is pointer
			bool isPointer() const;

			/// Checks if the type is class type
			bool isClass() const;

			/// Checks if the type is valid a.k.a not invalid type
			operator bool() const;

			Type& operator=(const Type& rhs);

			// these are needed for algorithms to work
			bool operator<(const Type& rhs) const;
			bool operator>(const Type& rhs) const;
			bool operator<=(const Type& rhs) const;
			bool operator>=(const Type& rhs) const;
			bool operator==(const Type& rhs) const;
			bool operator!=(const Type& rhs) const;

		private:
			TypeID id;
		};
	}
}

