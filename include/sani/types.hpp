#pragma once

#include <string>
#include <stdint.h>

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

// int8-64 assertions.
static_assert(sizeof(int8) == 1, "sizeof(int8) != 1");
static_assert(sizeof(int16) == 2, "sizeof(int16) != 2");
static_assert(sizeof(int32) == 4, "sizeof(int32) != 4");
static_assert(sizeof(int64) == 8, "sizeof(int64) != 8");

// uint8-64 assertions.
static_assert(sizeof(uint8) == 1, "sizeof(uint8) != 1");
static_assert(sizeof(uint16) == 2, "sizeof(uint16) != 2");
static_assert(sizeof(uint32) == 4, "sizeof(uint32) != 4");
static_assert(sizeof(uint64) == 8, "sizeof(uint64) != 8");

// float32-64 assertions.
static_assert(sizeof(float32) == 4, "sizeof(float32) != 4");
static_assert(sizeof(float64) == 8, "sizeof(float64) != 8");

static_assert(sizeof(char8) == 1, "sizeof(char8) != 1");
static_assert(sizeof(char16) == 2, "sizeof(char16) != 2");