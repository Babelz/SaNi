#include "sani/resource/texture2d.hpp"
#include "sani/core/logging/log.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform.hpp"
#include <algorithm>

namespace sani {

	namespace resource {

		using namespace graphics;

		Texture2D::Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height) : Texture(device, width, height), 
																										  levelCount(1) {
			generateTexture(device, width, height, false, SurfaceFormat::ColorRGBA);
		}

		Texture2D::Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap) : Texture(device, width, height), 
																														     levelCount(((mipmap) ? calculateLevelCount(width, height) : 1)) {
			generateTexture(device, width, height, mipmap, SurfaceFormat::ColorRGBA);
		}

		Texture2D::Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, const SurfaceFormat format) 
			: Texture(device, width, height), 
			  levelCount(((mipmap) ? calculateLevelCount(width, height) : 1)) {

			generateTexture(device, width, height, mipmap, format);
		}

		Texture2D::~Texture2D() {
			// TODO: deleting.
		}

		void Texture2D::generateTexture(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const bool mipmap, SurfaceFormat format) {
			graphics::TextureDescription desc;
			desc.width = width;
			desc.height = height;
			desc.format = format;
			desc.levels = levelCount;

			uint32 id = 0;
			device->generateTexture(id, desc);
			setID(id);

			TextureWrapMode wrap = TextureWrapMode::Repeat;
			// For best compatibility only set ClampToEdge if either
			// dimension is not a power of two.

			if (((width & (width - 1)) != 0) || ((height & (height - 1)) != 0)) {
				wrap = TextureWrapMode::ClampToEdge;
			}

			device->bindTexture(getID());

			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::TextureMagFilter,
				static_cast<int>(TextureMagFilter::Linear)
				);

			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::TextureMinFilter,
				static_cast<int>((mipmap) ? TextureMinFilter::LinearMipmapLinear : TextureMinFilter::Linear)
				);

			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::TextureWrapS,
				static_cast<int>(TextureWrapMode::ClampToEdge)
				);

			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::TextureWrapT,
				static_cast<int>(TextureWrapMode::ClampToEdge)
				);

			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::BaseLevel,
				0);
			
			device->setTextureParameter(
				TextureTarget::Texture2D,
				TextureParameterName::MaxLevel,
				static_cast<int>(levelCount));

			device->unbindTexture();
		}

		void Texture2D::setData(graphics::GraphicsDevice* device, const int level, const math::Rect32i* rect, const PixelData& data, const uint32 startIndex, const uint32 elementCount) {
			uint32 startBytes = sizeof(unsigned char) * startIndex;

			const unsigned char* ptr = data.data() + startIndex;

			if (rect != nullptr) {
				FLOG_ERR(log::OutFlags::All, "not implemented");

				std::abort();
			}

			int x, y, w, h;
			x = y = 0;
			w = std::max(getWidth() >> level, 1u);
			h = std::max(getHeight() >> level, 1u);

			device->bindTexture(getID());
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
				FLOG_ERR(log::OutFlags::All, "not implemented");

				std::abort();
			}

			device->bindTexture(getID());
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