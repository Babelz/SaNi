#pragma once

#include "sani/types.hpp"
#include <functional>

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
namespace sani {
	namespace graphics {
		enum class BufferUsage {
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
			Static = GL_STATIC_DRAW,

			// Buffers data will be modified repeatedly and used many times.
			Dynamic = GL_DYNAMIC_DRAW,

			// Buffers data will be changed after every use, or almost every use.
			Stream = GL_STREAM_DRAW
		};

		enum class BufferType {
			/*
				#define GL_ARRAY_BUFFER			0x8892
				#define GL_ELEMENT_ARRAY_BUFFER 0x8893
				*/

			ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
			ArrayBuffer = GL_ARRAY_BUFFER
		};

		enum class PrimitiveType {
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

			Byte = GL_BYTE,
			UByte = GL_UNSIGNED_BYTE,
			Short = GL_SHORT,
			UShort = GL_UNSIGNED_SHORT,
			Int = GL_INT,
			UInt = GL_UNSIGNED_INT,
			Float = GL_FLOAT,
			Double = GL_DOUBLE
		};

		enum class ShaderType {
			/*
				#define GL_FRAGMENT_SHADER	0x8B30
				#define GL_VERTEX_SHADER	0x8B31
				*/

			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER
		};

		enum class UniformType {
			// Data type expected: float 4 * 4.
			Mat4F,

			// Data type excepted: float 3 * 3.
			Mat3F
		};

		enum class RenderMode {
			/*
				#define GL_POINTS						0x0000
				#define GL_LINES						0x0001
				#define GL_LINE_LOOP					0x0002
				#define GL_LINE_STRIP					0x0003
				#define GL_TRIANGLES					0x0004
				#define GL_TRIANGLE_STRIP				0x0005
				#define GL_TRIANGLE_FAN					0x0006
				#define GL_LINES_ADJACENCY				0x000A
				#define GL_LINE_STRIP_ADJACENCY			0x000B
				#define GL_TRIANGLES_ADJACENCY			0x000C
				#define GL_TRIANGLE_STRIP_ADJACENCY		0x000D
				*/

			Points = GL_LINES,
			LineStrip = GL_LINE_STRIP,
			LineLoop = GL_LINE_LOOP,
			Lines = GL_LINES,
			LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
			LinesAdjacency = GL_LINES_ADJACENCY,
			TriangleStrip = GL_TRIANGLE_STRIP,
			TriangleFan = GL_TRIANGLE_FAN,
			Triangles = GL_TRIANGLES,
			TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
			TrianglesAdjancency = GL_TRIANGLES_ADJACENCY,
			Patches = GL_PATCHES
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

		enum class SurfaceFormat {
			ColorRGBA
		};

		enum class SurfaceType {
			Texture,
			RenderTarget
		};

		enum class TextureTarget : uint32 {
			Texture2D = GL_TEXTURE_2D,
			Texture3D = GL_TEXTURE_3D
		};

		enum class TextureParameterName : uint32 {
			TextureMagFilter = GL_TEXTURE_MAG_FILTER,
			TextureMinFilter = GL_TEXTURE_MIN_FILTER,
			TextureWrapS = GL_TEXTURE_WRAP_S,
			TextureWrapT = GL_TEXTURE_WRAP_T
		};

		enum class TextureWrapMode {
			Repeat = GL_REPEAT,
			MirroredRepeat = GL_MIRRORED_REPEAT,
			ClampToEdge = GL_CLAMP_TO_EDGE,
			ClampToBorder = GL_CLAMP_TO_BORDER
		};

		enum class TextureMagFilter {
			Nearest = GL_NEAREST,
			Linear = GL_LINEAR
		};

		enum class TextureMinFilter {
			Nearest = GL_NEAREST,
			Linear = GL_LINEAR,
			NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
			LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
			NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
			LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
		};

		struct TextureDescription {
			uint32 width;
			uint32 height;
			uint32 levels;
			SurfaceFormat format;
			SurfaceType type;

			TextureDescription()
				: width(0), height(0), levels(1), format(SurfaceFormat::ColorRGBA), type(SurfaceType::Texture) {}
		};
	}
}