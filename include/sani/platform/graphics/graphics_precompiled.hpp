#pragma once

#include "sani/types.hpp"
#include <functional>

typedef	int32 Buffer;
typedef int32 Shader;
typedef int32 RenderTexture;
typedef int32 ShaderProgram;

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "GL/glew.h"
#elif SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#endif

// Static assertions.
static_assert(sizeof(GLuint) == sizeof(uint32), "sizeof(GLuint) != sizeof(uint32)");
static_assert(sizeof(GLuint) == sizeof(Shader), "sizeof(GLuint) != sizeof(Shader)");
static_assert(sizeof(GLuint) == sizeof(Buffer), "sizeof(GLuint) != sizeof(Buffer)");
static_assert(sizeof(GLuint) == sizeof(RenderTexture), "sizeof(GLuint) != sizeof(RenderTexture)");


enum BufferUsage {
	// Buffers data will be modified once and used many times.
	Static,
	// Buffers data will be modified repearedly and used many times.
	Dynamic
};

enum BufferType {
	ElementArrayBuffer,
	ArrayBuffer
};

enum Type {
	UByte,
	UShort,
	UInt,
	Float
};

enum ShaderType {
	Vertex,
	Pixel
};

enum UniformType {
	// Data type expected: float 4 * 4.
	Mat4F,
	// Data type excepted: float 3 * 3.
	Mat3F
};

struct VertexAttributeDescription {
	uint32 location;
	uint32 elementsCount;

	Type type;

	bool normalized;

	uint32 stride;
	uint32 offset;
	
	
	VertexAttributeDescription() : location(0),
								   elementsCount(0),
								   type(Type::UByte),
								   normalized(false),
								   stride(0),
								   offset(0) {
	}

	~VertexAttributeDescription() {
	}
};

struct TextureDescription {
	uint32 width;
	uint32 height;

	TextureDescription() : width(0),
						   height(0) {
	}

	~TextureDescription() {
	}
};