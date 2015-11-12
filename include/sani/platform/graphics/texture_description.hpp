#pragma once

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
	}
}

