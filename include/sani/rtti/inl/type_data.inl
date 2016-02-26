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

		template <class ClassType, class FieldType>
		void TypeData::addField(const String8& name, Field::Getter getter, Field::Setter setter) {
			Field field(
				name,
				Type(TypeInfo<PureType<FieldType>>::id),
				Type(TypeInfo<PureType<ClassType>>::id),
				getter,
				setter
				);
			fields.emplace(name, field);
		}

		template <class MethodType, class MethodInvoker>
		void TypeData::addMethod(const String8& name, MethodType type, MethodInvoker invoker) {
			Method method(name, type, invoker);
			methods[name].emplace(method.getSignature(), method);
		}
	}
}

