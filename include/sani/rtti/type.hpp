#pragma once
#include "sani/rtti/argument_config.hpp"
#include "sani/rtti/type_config.hpp"

#include "sani/types.hpp"
#include "sani/forward_declare.hpp"
#include <set>
SANI_FORWARD_DECLARE_2(sani, rtti, Object);
SANI_FORWARD_DECLARE_2(sani, rtti, Field);
SANI_FORWARD_DECLARE_2(sani, rtti, Method);
SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);

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
			TypeID getID() const;

			/// Checks if the type is valid
			bool isValid() const;

			/// Checks if the type is pointer
			bool isPointer() const;

			/// Checks if the type is class type
			bool isClass() const;

			/// Checks if the type is valid a.k.a not invalid type
			operator bool() const;

			Type& operator=(const Type& rhs);

			/// Invokes constructor with specified arguments
			Object create(Arguments& args) const;

			/// Invokes dynamic constructor with specified args
			Object createDynamic(Arguments& args) const;

            Object createUsingService(Arguments& args) const;

			// these are needed for algorithms to work
			bool operator<(const Type& rhs) const;
			bool operator>(const Type& rhs) const;
			bool operator<=(const Type& rhs) const;
			bool operator>=(const Type& rhs) const;
			bool operator==(const Type& rhs) const;
			bool operator!=(const Type& rhs) const;

			/// Checks if the type is derived from other class
			/// @param other The possible base class
			/// @returns true if it's this types base class, false otherwise
			bool isDerivedFrom(const Type other) const;
			
			/// Checks if the type is derived from other class
			/// @tparam other The possible base class
			/// @returns true if it's this types base class, false otherwise
			template <class T>
			bool isDerivedFrom() const;

			/// Gets the fields for this type
			const std::vector<Field> getFields() const;

			/// Gets the field with specified name
			/// @param name the name of the field
			const Field& getField(const String8& name) const;

			const Method& getMethod(const String8& name) const;

			/// Gets all base classes from this class type
			const std::set<Type>& getBaseClasses() const;

			/// Gets all classes that derive from this class type
			const std::set<Type>& getDerivedClasses() const;

			/// Helper function to get types
			template <class T>
			static Type get(T&& v);

			
		private:
			TypeID id;
		};
	}
}

#include "inl/type.inl"