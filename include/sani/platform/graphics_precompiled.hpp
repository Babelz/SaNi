#pragma once

#include "GL/glew.h"
#include "sani/precompiled.hpp"
#include <functional>

typedef	int32 Buffer;
typedef int32 Shader;
typedef int32 RenderTexture;

// Static assertions.
static_assert(sizeof(GLuint) == sizeof(uint32), "sizeof(GLuint) != sizeof(uint32)");
static_assert(sizeof(GLuint) == sizeof(Shader), "sizeof(GLuint) != sizeof(Shader)");
static_assert(sizeof(GLuint) == sizeof(Buffer), "sizeof(GLuint) != sizeof(Buffer)");
static_assert(sizeof(GLuint) == sizeof(RenderTexture), "sizeof(GLuint) != sizeof(RenderTexture)");

enum BufferType {
	FrameBuffer
};