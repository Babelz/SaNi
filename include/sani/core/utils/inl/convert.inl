#include "sani/core/utils/convert.hpp"
#include <sstream>

namespace sani {

	namespace utils {

		inline int8 toInt8(const String& str) {
			return static_cast<int8>(toInt32(str));
		}
		inline int16 toInt16(const String& str) {
			return static_cast<int16>(toInt32(str));
		}
		inline int32 toInt32(const String& str) {
			static_assert(sizeof(int) == sizeof(int32), "size miss match");

			return std::stoi(str);
		}
		inline int64 toInt64(const String& str) {
			static_assert(sizeof(_Longlong) == sizeof(int64), "size miss match");

			return std::stoll(str);
		}

		inline uint8 toUInt8(const String& str) {
			return static_cast<uint8>(toUInt32(str));
		}
		inline uint16 toUInt16(const String& str) {
			return static_cast<uint16>(toUInt32(str));
		}
		inline uint32 toUInt32(const String& str) {
			static_assert(sizeof(unsigned int) == sizeof(uint32), "size miss match");
			
			/*
				TODO: is this x platform?
			*/

			std::istringstream reader(str);

			uint32 value = 0;

			reader >> value;

			return value;
		}
		inline uint64 toUInt64(const String& str) {
			static_assert(sizeof(_ULonglong) == sizeof(uint64), "size miss match");

			return std::stoull(str);
		}

		inline float32 toFloat32(const String& str) {
			return std::stof(str);
		}
		inline float64 toFloat64(const String& str) {
			return std::stod(str);
		}
	}
}