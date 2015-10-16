#pragma once

#include "sani/types.hpp"
#include <functional>

typedef	uint32 Buffer;
typedef uint32 Shader;
typedef uint32 RenderTexture;
typedef uint32 ShaderProgram;

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "GL/glew.h"
#elif SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#endif

// Static assertions.
static_assert(sizeof(GLuint) == sizeof(uint32), "sizeof(GLuint) != sizeof(uint32)");

/*
	TODO: when implementing DirectX begins, 
		  create two headers that contain 
		  mappings for OpenGL and DirectX.
	      
		  The ones defined here are for OpenGL.

		  All GL functionalities are not supported
		  yet and many of the will never be implemented.
*/

enum BufferUsage {
	/*
	
		#define GL_STREAM_DRAW		0x88E0
		#define GL_STREAM_READ		0x88E1
		#define GL_STREAM_COPY		0x88E2
		#define GL_STATIC_DRAW		0x88E4
		#define GL_STATIC_READ		0x88E5
		#define GL_STATIC_COPY		0x88E6
		#define GL_DYNAMIC_DRAW		0x88E8
		#define GL_DYNAMIC_READ		0x88E9
		#define GL_DYNAMIC_COPY		0x88EA
		#define GL_SAMPLES_PASSED	0x8914

	*/
	
	// Buffers data will be modified once and used many times.
	Static	= 0x88E4,

	// Buffers data will be modified repeatedly and used many times.
	Dynamic = 0x88E8
};

enum BufferType {
	/*
		#define GL_ARRAY_BUFFER			0x8892
		#define GL_ELEMENT_ARRAY_BUFFER 0x8893
	*/

	ElementArrayBuffer	= 0x8893,
	ArrayBuffer			= 0x8892
};

enum PrimitiveType {
	/*
		#define GL_BYTE				0x1400
		#define GL_UNSIGNED_BYTE	0x1401
		#define GL_SHORT			0x1402
		#define GL_UNSIGNED_SHORT	0x1403
		#define GL_INT				0x1404
		#define GL_UNSIGNED_INT		0x1405
		#define GL_FLOAT			0x1406
		#define GL_DOUBLE			0x140A
	*/

	Byte	= 0x1400,
	UByte	= 0x1401,
	Short	= 0x1402,
	UShort	= 0x1403,
	Int		= 0x1404,
	UInt	= 0x1405,
	Float	= 0x1406,
	Double	= 0x140A
};

enum ShaderType {
	/*
		#define GL_FRAGMENT_SHADER	0x8B30
		#define GL_VERTEX_SHADER	0x8B31
	*/

	Vertex	 = 0x8B31,
	Fragment = 0x8B30
};

enum UniformType {
	// Data type expected: float 4 * 4.
	Mat4F,

	// Data type excepted: float 3 * 3.
	Mat3F
};

enum RenderMode {
	/*
		#define GL_POINTS 0x0000
		#define GL_LINES 0x0001
		#define GL_LINE_LOOP 0x0002
		#define GL_LINE_STRIP 0x0003
		#define GL_TRIANGLES 0x0004
		#define GL_TRIANGLE_STRIP 0x0005
		#define GL_TRIANGLE_FAN 0x0006
	*/

	Points = 0x0000,
	LineStrip = 0x0003,
	LineLoop = 0x0002,
	Lines = 0x0001,
	LineStripAdjacency = ,
	LinesAdjacency = ,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan = GL_TRIANGLE_FAN,
	Triangles = ,
	TriangleStripAdjacency = ,
	TrianglesAdjancency = ,
	Patches =
};

struct VertexAttributePointerDescription  {
	uint32 location;
	uint32 count;

	PrimitiveType type;
	bool normalized;

	uint32 stride;
	uint32 offset;

	VertexAttributePointerDescription() : location(0),
										  count(0), 
										  type(PrimitiveType::UByte),
										  normalized(false),
										  stride(0),
										  offset(0) {
	}

	~VertexAttributePointerDescription() {
	}
};