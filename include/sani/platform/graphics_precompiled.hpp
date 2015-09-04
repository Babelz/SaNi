#pragma once

#include "sani/precompiled.hpp"
#include "GL/glew.h"
#include <functional>

typedef	int32 Buffer;
typedef int32 Shader;
typedef int32 RenderTexture;

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID
#include "GL/glew.h"
// Static assertions.
static_assert(sizeof(GLuint) == sizeof(uint32), "sizeof(GLuint) != sizeof(uint32)");
static_assert(sizeof(GLuint) == sizeof(Shader), "sizeof(GLuint) != sizeof(Shader)");
static_assert(sizeof(GLuint) == sizeof(Buffer), "sizeof(GLuint) != sizeof(Buffer)");
static_assert(sizeof(GLuint) == sizeof(RenderTexture), "sizeof(GLuint) != sizeof(RenderTexture)");
#endif 
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

enum ShaderType {
	Vertex,
	Pixel
};