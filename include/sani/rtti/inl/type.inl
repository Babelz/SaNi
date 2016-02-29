#pragma once

namespace sani {
	namespace rtti {
		template <class T>
		bool Type::isDerivedFrom() const {
			return isDerivedFrom(typeof(T));
		}

		template <class T>
		Type Type::get(T&& v) {
			return typeof(T);
		}
	}
}

