#pragma once
#include "sani/rtti/constructor.hpp"
namespace sani {
	namespace rtti {
		template <class Class>
		void TypeData::addConstructor(Constructor::CreateInstance func, bool isDynamic) {
			Signature signature;
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

