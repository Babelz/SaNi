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

			/// Is this pointer type?
			bool isPointer : 1;
			/// Is this class type?
			bool isClass : 1;
			char __padding[2];
		};
		

	}
}

