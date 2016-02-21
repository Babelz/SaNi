#pragma once
#include <vector>
#include "sani/rtti/type.hpp"
#include "sani/forward_declare.hpp"
SANI_FORWARD_DECLARE_2(sani, rtti, Object);

namespace sani {
	namespace rtti {
		class Argument {
		public:
			/// Constructs invalid argument
			Argument();
			/// Constructs copy of argument
			Argument(const Argument& rhs);

			template <class T>
			Argument(const T& data);

			/// Copies the argument
			Argument& operator=(const Argument& rhs);

			/// Gets the argument type
			Type getType() const;

			/// Gets the pointer to data
			void* getPointer() const;

			/// Gets the value of argument
			template <class T>
			T& getValue() const;
		private:
			const Type type;
			const void* ptr;
		};
	}
}

#include "inl/argument.inl"