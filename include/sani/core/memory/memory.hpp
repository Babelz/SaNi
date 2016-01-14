#pragma once

#include "sani\types.hpp"

#include <cstdint>

template<typename T>
inline void NEW_DYNAMIC_DEFAULT(T* const ptr) {
	new (ptr)T();
}

template<typename T>
inline void NEW_DYNAMIC(T* const ptr, ...) {
	new (ptr)T(__VA_ARGS__);
}

const int32 BLOCK_1KB		= 1024;
const int32 BLOCK_2KB		= 2048;
const int32 BLOCK_4KB		= 4096;
const int32 BLOCK_8KB		= 8192;
const int32 BLOCK_16KB		= 16384;
const int32 BLOCK_32KB		= 32768;
const int32 BLOCK_64KB		= 65536;
const int32 BLOCK_128KB		= 131072;
const int32 BLOCK_256KB		= 262144;
const int32 BLOCK_512KB		= 524288;
const int32 BLOCK_1024KB	= 1048576;

using IntPtr = uintptr_t;