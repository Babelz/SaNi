#pragma once
#include <xhash>

namespace std {
	template <>
	struct hash<sani::rtti::Signature> {
		size_t operator()(const sani::rtti::Signature& sig) {
			size_t seed = 0;
			for (auto& type : sig)
				seed ^= hash_value(type.getID()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			return seed;
		}
	};
}

namespace sani {
	namespace rtti {

		template <class... T>
		struct Unpack {};

		template<>
		struct Unpack<> {
			static void apply(std::vector<Type>&) {}
		};

		template <class Head, class... Tail>
		struct Unpack<Head, Tail...> {
			static void apply(std::vector<Type>& types) {
				types.emplace_back(Type(TypeInfo<PureType<Head>>::id));
				Unpack<Tail...>::apply(types);
			}
		};

		template <typename ...Types>
		Signature Invokable::createSignature() {
			static Signature sig;
			static auto init = true;
			if (init) {
				Unpack<Types...>::apply(sig);
				init = false;
			}
			return sig;
		}
	}
}