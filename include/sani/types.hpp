#pragma once

#include <string>
#include <stdint.h>

typedef std::string String;

// int8-64 definitions.
typedef	int8_t		int8;
typedef int16_t		int16;
typedef int32_t		int32;
typedef int64_t     int64;

// uint8-64 definitions.
typedef uint8_t		uint8;
typedef uint16_t	uint16;
typedef	uint32_t	uint32;
typedef uint64_t    uint64;

// f32-64 definitions.
typedef float		float32;
typedef double		float64;

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