#pragma once

#include "sani/types.hpp"

/// Provides the compile time reader to be used to read this type of
/// resource
template <typename T> class DeserializableWith {
public:
	static String value() {
		// TODO error
		static_assert(0, "This type doesnt have serialization specified");
	}
};

#define SANI_DESERIALIZABLE_WITH(c, c1)\
template<> class DeserializableWith<c> { \
public: static String value() { return #c1; } };