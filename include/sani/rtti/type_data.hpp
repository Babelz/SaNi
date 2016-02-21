#pragma once

#include "sani/types.hpp"
#include "sani/rtti/constructor.hpp"
#include <unordered_map>
namespace sani {
	namespace rtti {

		using Constructors = std::unordered_map<Signature, Constructor>;

		/// Structure which represents all the data contained within type
		/// constructors, fields, methods
		struct TypeData {
			/// The name of the type
			String8 name;

			/// Constructs invalid type data object
			TypeData();
			/// Constructs valid type data object
			TypeData(const String& name);

			Constructors constructors;
			Constructors dynamicConstructors;

			/// Gets constructor which matches the signature
			/// @param signature The signature to search for
			const Constructor& getConstructor(const Signature& signature);

			/// Gets dynamic constructor which matches the signature
			/// @param signature The signature to search for
			const Constructor& getDynamicConstructor(const Signature& signature);

			/// Adds constructor for type 
			/// @param func Function containing the initialization
			/// @param isDynamic Is this dynamic constructor
			template <class Class>
			void addConstructor(Constructor::CreateInstance func, bool isDynamic);

			/// Is this pointer type?
			bool isPointer : 1;
			/// Is this class type?
			bool isClass : 1;
			char __padding[2];
		};
		

	}
}

#include "inl/type_data.inl"