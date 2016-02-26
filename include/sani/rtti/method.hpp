#pragma once

#include "sani/rtti/invokable.hpp"
#include <functional>
#include "sani/rtti/object.hpp"
#include "sani/rtti/argument_config.hpp"

namespace sani {
	namespace rtti {
		class Method : public Invokable {
		public:
			using Invoker = std::function<Object(Object&, Arguments&)>;

			/// Creates invalid method
			Method();

			/// Non-const functions
			template <class ClassType, typename Ret, typename ...Args>
			Method(const String8& name,
				Ret(ClassType::*method)(Args...),
				Invoker invoker);

			/// Const functions
			template <class ClassType, typename Ret, typename ...Args>
			Method(const String8& name,
				Ret(ClassType::*method)(Args...) const,
				Invoker invoker);

			/// Gets the type of the class this method belongs to
			Type getClassType() const;

			/// Checks if the method has valid func pointer
			bool isValid() const; 

			/// Chekcs if the method is const
			bool isConst() const;

			/// Invokes the method
			/// @param instance Existing instance of class where this method points to
			/// @param args Arguments to pass to method
			/// @returns The return value, can be void
			Object invoke(Object& instance, Arguments& args) const;

			/// Returns cached invalid method pointer
			static const Method& invalid();
		private:
			Type classType;
			Invoker invoker;
			bool _isConst;
		};
	}
}

#include "inl/method.inl"
