#pragma once

#include "sani/types.hpp"
#include "sani/resource/compiler/resource_type_writer.hpp"

/// Provides the compile time reader to be used to read this type of
/// resource
template <typename T> class DeserializableWith {
public:
	static String value() {
		// TODO error
		return String();
		//static_assert(0, "This type doesnt have serialization specified");
	}
};

#if 0
template <class T> class SerializableWith {
public:
	static sani::resource::compiler::ResourceTypeWriter* value() {
		// TODO error
		//static_assert(0, "This type doesnt have serialization specified");
		return String();
	}
};
#endif

#define SANI_DESERIALIZABLE_WITH(c, c1)\
template<> class DeserializableWith<c> { \
public: static String value() { return #c1; } };

#define SANI_SERIALIZABLE_WITH(c, c1) \
template<> class SerializableWith<c> { \
	public: static sani::resource::compiler::ResourceTypeWriter* value() { \
		return new c1; } };
