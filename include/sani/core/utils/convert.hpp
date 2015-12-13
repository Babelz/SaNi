#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace utils {
		
		inline int8 toInt8(const String& str);
		inline int16 toInt16(const String& str);
		inline int32 toInt32(const String& str);
		inline int64 toInt64(const String& str);

		inline uint8 toUInt8(const String& str);
		inline uint16 toUInt16(const String& str);
		inline uint32 toUInt32(const String& str);
		inline uint64 toUInt64(const String& str);

		inline float32 toFloat32(const String& str);
		inline float64 toFloat64(const String& str);
	}
}

#include "sani/core/utils/inl/convert.inl"