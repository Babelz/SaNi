#include "sani/types.hpp"

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

#if SANI_TARGET_ARCH == SANI_ARCH_X64
static_assert(sizeof(SizeType) == sizeof(uint64), "SizeType is invalid");
static_assert(sizeof(SignedSizeType) == sizeof(int64), "SignedSizeType is invalid");
#else
static_assert(sizeof(SizeType) == sizeof(uint64), "SizeType is invalid");
static_assert(sizeof(SignedSizeType) == sizeof(int64), "SignedSizeType is invalid");
#endif