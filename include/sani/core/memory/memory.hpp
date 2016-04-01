#pragma once

#include "sani\types.hpp"

#define NEW_DYNAMIC(type, ptr, ...)		new (ptr)type(##__VA_ARGS__)
#define NEW_DYNAMIC_DEFAULT(type, ptr)	new (ptr)type()

const int32 Block1Kb		= 1024;
const int32 Block2Kb		= 2048;
const int32 Block4Kb		= 4096;
const int32 Block8Kb		= 8192;
const int32 Block16Kb		= 16384;
const int32 Block32Kb		= 32768;
const int32 Block64Kb		= 65536;
const int32 Block128Kb		= 131072;
const int32 Block256Kb		= 262144;
const int32 Block512Kb		= 524288;
const int32 Block1024Kb		= 1048576;

// On ARM and X86 platforms the word size should be 4-bytes.
const int32 WordSize		= sizeof(int);

using IntPtr				= uintptr_t;

static_assert(WordSize == 4, "WORD_SIZE != 4");

namespace sani {

	inline uint32 pad(const uint32 bytes);
}

#include "sani/core/memory/inl/memory.inl"