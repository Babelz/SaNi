#pragma once

#include "sani\types.hpp"

#include <cstdint>

#define NEW_DYNAMIC(type, ptr, ...) new (ptr)type(##__VA_ARGS__)
#define NEW_DYNAMIC_DEFAULT(type, ptr) new (ptr)type()

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

// On ARM and X86 platforms the word size should be 4-bytes.
// Could this check be done at compile time.
const int32 WORD_SIZE		= sizeof(int);

using IntPtr				= uintptr_t;

static_assert(WORD_SIZE == 4, "WORD_SIZE != 4");

namespace sani {

	/// Returns the aligned bytes count.
	inline uint32 align(const uint32 bytes);
}

#include "sani/core/memory/inl/memory.inl"