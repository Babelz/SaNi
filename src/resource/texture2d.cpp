#include "sani/resource/texture2d.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/texture_description.hpp"
namespace sani {
	namespace resource {
		using namespace graphics;
		Texture2D::Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height)
			: Texture(device, width, height), levelCount(1) {
			generateTexture(device, width, height, false, SurfaceFormat::ColorRGBA, SurfaceType::Texture);
		}

		Texture2D::Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, SurfaceFormat format)
			: Texture(device, width, height), levelCount(((mipmap) ? calculateLevelCount(width, height) : 1)) {
			generateTexture(device, width, height, mipmap, format, SurfaceType::Texture);
		}

		Texture2D::Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, 
							 const bool mipmap, const SurfaceFormat format, const SurfaceType type)
							 : Texture(device, width, height), levelCount(((mipmap) ? calculateLevelCount(width, height) : 1)) {
			generateTexture(device, width, height, mipmap, format, type);
		}

		Texture2D::~Texture2D() {}

		void Texture2D::generateTexture(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, SurfaceFormat format, SurfaceType type) {
			graphics::TextureDescription desc;
			desc.width = width;
			desc.height = height;
			desc.format = format;
			desc.type = type;
			desc.levels = levelCount;
			device->generateTexture(renderTexture, desc);
		}

		uint32 Texture2D::calculateLevelCount(uint32 width, uint32 height) {
			uint32 levels = 0;
			while (width > 1 && height > 1) {
				++levels;
				width /= 2;
				height /= 2;
			}
			return levels;
		}
	}
}