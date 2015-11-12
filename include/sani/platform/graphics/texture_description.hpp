#pragma once
#include "sani/platform/platform_config.hpp"
#include "sani/types.hpp"
#include "sani/platform/graphics/texture.hpp"
namespace sani {
	namespace graphics {
		struct TextureDescription {
			uint32 width;
			uint32 height;
			uint32 levels;
			SurfaceFormat format;
			SurfaceType type;

			TextureDescription() 
				: width(0), height(0), levels(1), format(ColorRGBA), type(SurfaceType::Texture) {}
		};

		enum class TextureParameterName {
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
			Linear = GL_LINEAR,
			Nearest = GL_NEAREST
		};

		enum class TextureMinFilter {
			Linear = GL_LINEAR,
			Nearest = GL_NEAREST,
			NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
			LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
			NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
			LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
		};
	}
}

