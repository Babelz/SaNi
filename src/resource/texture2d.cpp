#include "sani/resource/texture2d.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform.hpp"
#include <algorithm>
#include <stdexcept>


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

		Texture2D::~Texture2D() {
			
		}

		void Texture2D::generateTexture(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, SurfaceFormat format, SurfaceType type) {
			graphics::TextureDescription desc;
			desc.width = width;
			desc.height = height;
			desc.format = format;
			desc.type = type;
			desc.levels = levelCount;
			device->generateTexture(renderTexture, desc);
			
			TextureWrapMode wrap = TextureWrapMode::Repeat;
			// For best compatibility only set ClampToEdge if either
			// dimension is not a power of two.
			if (((width & (width - 1)) != 0) || ((height & (height - 1)) != 0)) {
				wrap = TextureWrapMode::ClampToEdge;
			}

			device->bindTexture(renderTexture);
			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::TextureMinFilter,
				static_cast<int>((mipmap) ? TextureMinFilter::LinearMipmapLinear : TextureMinFilter::Linear)
				);
			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::TextureMagFilter,
				static_cast<int>(TextureMagFilter::Linear)
				);
			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::TextureWrapS,
				static_cast<int>(wrap)
				);
			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::TextureWrapT,
				static_cast<int>(wrap)
				);


			device->unbindTexture();
		}

		void Texture2D::setData(graphics::GraphicsDevice* device, const int level, const math::Rect32i* rect, const PixelData& data, const uint32 startIndex, const uint32 elementCount) {
			uint32 startBytes = sizeof(unsigned char) * startIndex;
			const unsigned char* ptr = data.data() + startIndex;
			if (rect != nullptr) {
				throw std::logic_error("not implemented");
			}
			int x, y, w, h;
			x = y = 0;
			w = std::max(getWidth() >> level, 1u);
			h = std::max(getHeight() >> level, 1u);

			device->bindTexture(renderTexture);
			device->setTextureData(
				TextureTarget::Texture2D,
				level,
				SurfaceFormat::ColorRGBA,
				w,
				h,
				SurfaceFormat::ColorRGBA,
				data.data()
				);
			device->unbindTexture();
		}

		void Texture2D::getData(graphics::GraphicsDevice* device, const int level, const math::Rect32i* rect, PixelData& data, const uint32 startIndex, const uint32 elementCount) {
			if (rect != nullptr) {
				throw std::logic_error("Not implemented");
			}
			device->bindTexture(renderTexture);
			data.reserve(getWidth() * getHeight() * 4);
			device->getTextureData(
				TextureTarget::Texture2D,
				level,
				SurfaceFormat::ColorRGBA,
				data.data()
				);
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