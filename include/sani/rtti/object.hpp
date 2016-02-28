#pragma once

#include "sani/rtti/object_base.hpp"
#include "sani/rtti/object_container.hpp"
#include "sani/rtti/pointer_container.hpp"
#include "sani/rtti/type_config.hpp"
#include <type_traits>
namespace sani {
	namespace rtti {
		/// Class that represents every type there is
		class Object {
		public:
			Object();

			template<class T>
			Object(T& data);

			// only derived classes of Serializable are allowed
			template<class T>
			Object(T* data, typename std::enable_if<std::is_base_of<Reflectable, T>::value>::type*);

			// restrict objects
			template <class T>
			Object(T&& data,
				typename std::enable_if <!std::is_same<Object&, T>::value>::type* = nullptr,
				typename std::enable_if<!std::is_const<T>::value>::type* =  nullptr);

			Object(const Object& rhs);
			Object(Object&& rhs);
			~Object();

			template <class T>
			Object& operator=(T&& rhs);
			Object& operator=(Object&& rhs);
			Object& operator=(Object& rhs);

			/// Gets the underlaying type
			Type getType() const;

			/// Checks if the object is valid
			bool isValid() const;

			/// Checks if the object is const
			bool isConst() const;

			/// Returns the pointer to data
			void* getPointer() const;

			template <typename T>
			T& getValue() const;
		private:
			ObjectBase* _base;
			bool _isConst;
		};
	}
}

#include "inl/object.inl"