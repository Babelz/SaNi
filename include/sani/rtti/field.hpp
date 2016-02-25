#pragma once

#include <functional>
#include "sani/rtti/object.hpp"
#include "sani/types.hpp"

namespace sani {
	namespace rtti {
		class Field {
		public:
			using Getter = std::function<Object(const Object&)>;
			using Setter = std::function<void(Object&, const Object&)>;

			/// Creates invalid field
			Field();

			/// Creates field with name
			/// @param name The name of the field
			/// @param type The type of the field
			/// @param classType The type of class where this field belongs to
			/// @param getter The getter function for field
			/// @param setter The setter function for field
			Field(const String8& name, Type type, Type classType, Getter getter, Setter setter);

			/// Checks if the field is valid
			bool isValid() const;

			/// Checks if the field has setter specified
			bool isReadOnly() const;

			/// Gets the type of the field
			Type getType() const;

			/// Gets the type of class where this field belongs to
			Type getClassType() const;

			/// Gets the name of the field
			const String8& getName() const;

			/// Gets the value of the field using getter function
			Object getValue(Object& instance) const;

			/// Sets the value of the field using setter if its non-const
			/// @param instance The current instance of the field
			/// @param newValue The new value which will be assigned to field
			/// @returns true if its possible to 
			bool setValue(Object& instance, const Object& newValue) const;

		private:
			Type type;
			Type classType;
			String8 name;
			Getter getter;
			Setter setter;
		};
	}
}

