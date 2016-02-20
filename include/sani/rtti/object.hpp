#pragma once

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

		};
	}
}