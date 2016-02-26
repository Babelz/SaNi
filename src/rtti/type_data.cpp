#include "sani/rtti/type_data.hpp"

namespace sani {
	namespace rtti {

		TypeData::TypeData() 
			: isPointer(false), isClass(false) {

		}

		TypeData::TypeData(const String& name) 
			: name(name), isPointer(false), isClass(false) {

		}

		const Constructor& TypeData::getConstructor(const Signature& signature) {
			auto s = constructors.find(signature);
			if (s == constructors.end()) return Constructor::invalid();
			return s->second;
		}

		const Constructor& TypeData::getDynamicConstructor(const Signature& signature) {
			auto s = dynamicConstructors.find(signature);
			if (s == dynamicConstructors.end()) return Constructor::invalid();
			return s->second;
		}

		const Method& TypeData::getMethod(const String8& name) const {
			auto& base = methods.at(name);

			if (!base.size())
				return Method::invalid();

			return base.begin()->second;
		}

		const Method& TypeData::getMethod(const String8& name, const Signature& signature) const {
			auto &base = methods.at(name);

			auto search = base.find(signature);

			if (search == base.end())
				return Method::invalid();

			return search->second;
		}

	}
}