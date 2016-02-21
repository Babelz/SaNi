#pragma once
#include "sani/rtti/constructor.hpp"
namespace sani {
	namespace rtti {
		template <class Class, typename ... Args>
		void TypeData::addConstructor(Constructor::CreateInstance func, bool isDynamic) {
			Signature signature = Invokable::createSignature<Args...>();
			Constructor ctor{
				Type(TypeInfo<PureType<Class> >::id),
				signature,
				func,
				isDynamic
			};

			if (!isDynamic)
				constructors.emplace(signature, ctor);
			else
				dynamicConstructors.emplace(signature, ctor);
		}
	}
}

