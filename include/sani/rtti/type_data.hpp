#pragma once

#include "sani/types.hpp"
#include "sani/rtti/constructor.hpp"
#include "sani/rtti/field.hpp"
#include "sani/rtti/method.hpp"
#include <unordered_map>
#include <set>
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, rtti, TypeDatabase);

namespace sani {
	namespace rtti {

		using Constructors = std::unordered_map<Signature, Constructor>;
		using Fields = std::unordered_map<String8, Field>;
		using Methods = std::unordered_map<String8, std::unordered_multimap<Signature, Method> >;
		/// Structure which represents all the data contained within type
		/// constructors, fields, methods
		struct TypeData {
			/// The name of the type
			String8 name;
			std::set<Type> baseClasses;
			std::set<Type> derivedClasses;
			/// Constructs invalid type data object
			TypeData();
			/// Constructs valid type data object
			TypeData(const String& name);

			Constructors constructors;
			Constructors dynamicConstructors;
            Constructors serviceConstructors;
			Fields fields;
			Methods methods;
			/// Gets constructor which matches the signature
			/// @param signature The signature to search for
			const Constructor& getConstructor(const Signature& signature);

			/// Gets dynamic constructor which matches the signature
			/// @param signature The signature to search for
			const Constructor& getDynamicConstructor(const Signature& signature);

            /// Gets service constructor which matches the signature
            /// @param signature The signature to search for
            const Constructor& getServiceConstructor(const Signature& signature);

			/// Gets the first method by specified name
			/// @param name The name of the method
			const Method& getMethod(const String8& name) const;

			/// Gets method by specified name  and signature
			/// @param name The name of the method
			/// @param signature The signature of the method
			const Method& getMethod(const String8& name, const Signature& signature) const;


			void loadBaseClasses(TypeDatabase& db, TypeID thisType, const std::initializer_list<Type>& classes);

			/// Adds constructor for type 
			/// @param func Function containing the initialization
			/// @param isDynamic Is this dynamic constructor
			template <class Class, typename ...Args>
			void addConstructor(Constructor::CreateInstance func, bool isDynamic);

            template <class Class, typename ...Args>
            void addServiceConstructor(Constructor::CreateInstance func);

			template <class Class, class FieldType>
			void addField(const String8& name, Field::Getter getter, Field::Setter setter);

			template <class MethodType, class MethodInvoker>
			void addMethod(const String8& name, MethodType type, MethodInvoker invoker);

			/// Is this pointer type?
			bool isPointer : 1;
			/// Is this class type?
			bool isClass : 1;
		};
		

	}
}

#include "inl/type_data.inl"