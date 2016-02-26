#include "sani/preprocessor/rtti_runtime.hpp"

namespace sani {
	namespace rtti {

		template <class ClassType, typename Ret, typename ...Args>
		Method::Method(const String8& name,
			Ret(ClassType::*method)(Args...),
			Invoker invoker)
			: Invokable(name), 
			_isConst(false), 
			classType(typeof(ClassType)),
			invoker(invoker) {
			Unpack<Args...>::apply(signature);
		}

		template <class ClassType, typename Ret, typename ...Args>
		Method::Method(const String8& name,
			Ret(ClassType::*method)(Args...) const,
			Invoker invoker)
			: Invokable(name),
			_isConst(true),
			classType(typeof(ClassType)),
			invoker(invoker) {
			Unpack<Args...>::apply(signature);
		}

	}
}