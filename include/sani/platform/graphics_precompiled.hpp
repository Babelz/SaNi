#pragma once

#include "sani/precompiled.hpp"
#include "GL/glew.h"
#include <functional>

typedef	int32 Buffer;
typedef int32 Shader;
typedef int32 RenderTexture;

// Static assertions.
static_assert(sizeof(GLuint) == sizeof(uint32), "sizeof(GLuint) != sizeof(uint32)");
static_assert(sizeof(GLuint) == sizeof(Shader), "sizeof(GLuint) != sizeof(Shader)");
static_assert(sizeof(GLuint) == sizeof(Buffer), "sizeof(GLuint) != sizeof(Buffer)");
static_assert(sizeof(GLuint) == sizeof(RenderTexture), "sizeof(GLuint) != sizeof(RenderTexture)");

enum ElementBufferUsage {
	// Buffers data will be modified once and used many times.
	Static,
	// Buffers data will be modified repearedly and used many times.
	Dynamic
};

enum BufferType {
	ElementArrayBuffer,
	ArrayBuffer
};

enum IndicesType {
	UByte,
	UShort,
	UInt
};