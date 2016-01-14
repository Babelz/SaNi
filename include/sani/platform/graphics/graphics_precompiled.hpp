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
			// Buffers data will be modified once and used many times.
			Static	= GL_STATIC_DRAW,

			// Buffers data will be modified repeatedly and used many times.
			Dynamic = GL_DYNAMIC_DRAW,

			// Buffers data will be changed after every use, or almost every use.
			Stream  = GL_STREAM_DRAW
		};

		enum class BufferType {
			ElementArrayBuffer = GL_ELEMENT_ARRAY_BUFFER,
			ArrayBuffer		   = GL_ARRAY_BUFFER
		};

		enum class PrimitiveType {
			Byte    = GL_BYTE,
			UByte   = GL_UNSIGNED_BYTE,
			Short   = GL_SHORT,
			UShort  = GL_UNSIGNED_SHORT,
			Int     = GL_INT,
			UInt    = GL_UNSIGNED_INT,
			Float   = GL_FLOAT
		};

		enum class ShaderType {
			Vertex   = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER
		};

		enum class UniformType {
			// Data type expected: float 4 * 4.
			Mat4F,

			// Data type excepted: float 3 * 3.
			Mat3F
		};

		enum class RenderMode {
			Points    = GL_LINES,
			LineStrip = GL_LINE_STRIP,
			LineLoop  = GL_LINE_LOOP,
			Lines     = GL_LINES,

#if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID
			LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
			LinesAdjacency     = GL_LINES_ADJACENCY,
#endif

			TriangleStrip = GL_TRIANGLE_STRIP,
			TriangleFan   = GL_TRIANGLE_FAN,
			Triangles     = GL_TRIANGLES,

#if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID
			TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
			TrianglesAdjancency    = GL_TRIANGLES_ADJACENCY,
			Patches			       = GL_PATCHES
#endif
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

#if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID
			Texture3D = GL_TEXTURE_3D
#endif
		};

		enum class TextureParameterName : uint32 {
			TextureMagFilter = GL_TEXTURE_MAG_FILTER,
			TextureMinFilter = GL_TEXTURE_MIN_FILTER,
			TextureWrapS	 = GL_TEXTURE_WRAP_S,
			TextureWrapT	 = GL_TEXTURE_WRAP_T
		};

		enum class TextureWrapMode {
			Repeat		   = GL_REPEAT,
			MirroredRepeat = GL_MIRRORED_REPEAT,
			ClampToEdge    = GL_CLAMP_TO_EDGE,

#if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID
			ClampToBorder  = GL_CLAMP_TO_BORDER
#endif
		};

		enum class TextureMagFilter {
			Nearest = GL_NEAREST,
			Linear  = GL_LINEAR
		};

		enum class TextureMinFilter {
			Nearest				 = GL_NEAREST,
			Linear				 = GL_LINEAR,
			NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
			LinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
			NearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
			LinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR
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