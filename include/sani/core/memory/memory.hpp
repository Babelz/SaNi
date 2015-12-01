#pragma once

#include <cstdint>

#define NEW_DYNAMIC_DEFAULT(type, ptr)	new (ptr) type()
#define NEW_DYNAMIC(type, ptr, ...)	    new (ptr) type(##__VA_ARGS__)

#define BLOCK_1KB		1024
#define BLOCK_2KB		2048
#define BLOCK_4KB		4096
#define BLOCK_8KB		8192
#define BLOCK_16KB		16384
#define BLOCK_32KB		32768
#define BLOCK_64KB		65536
#define BLOCK_128KB		131072
#define BLOCK_256KB		262144
#define BLOCK_512KB		524288
#define BLOCK_1024KB	1048576

typedef uintptr_t IntPtr;