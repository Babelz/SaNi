#pragma once

#include <string>
#include <stdint.h>
#include "sani/platform/platform_config.hpp"

// int8-64 definitions.
using int8		= int8_t;
using int16		= int16_t;
using int32		= int32_t;
using int64		= int64_t;

// uint8-64 definitions.
using uint8		= uint8_t;
using uint16	= uint16_t;
using uint32	= uint32_t;
using uint64	= uint64_t;

// f32-64 definitions.
using float32	= float;
using float64	= double;

using char8 = char;
using char16 = wchar_t;

using String8 = std::basic_string < char8, std::char_traits<char8>, std::allocator<char8> >;
using String16 = std::basic_string < char16, std::char_traits<char16>, std::allocator<char16> >;
using String = String8;

#if SANI_TARGET_ARCH == SANI_ARCH_X64
using SizeType = uint64;
using SignedSizeType = int64;
#else
using SizeType = uint32;
using SignedSizeType = int32;
#endif