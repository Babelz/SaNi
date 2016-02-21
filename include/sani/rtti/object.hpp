#pragma once

#include "sani/rtti/object_base.hpp"
#include "sani/rtti/object_container.hpp"
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

			template<class T>
			Object(T* data);

			template <class T>
			Object(T&& data);

			Object(const Object& rhs);
			Object(Object&& rhs);
			~Object();

			template <class T>
			Object& operator=(T&& rhs);
			Object& operator=(Object&& rhs);
			Object& operator=(Object& rhs);

			/// Gets the underlaying type
			Type getType() const;
		private:
			ObjectBase* _base;
			bool _isConst;
		};
	}
}

#include "inl/object.inl"