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