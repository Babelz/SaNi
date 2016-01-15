#pragma once

#include <string>
#include <stdint.h>

using String	= std::string;

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