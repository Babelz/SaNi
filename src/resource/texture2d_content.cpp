#include "sani/platform/platform_config.hpp"
#include "sani/resource/texture2d_content.hpp"
#include "sani/core/logging/log.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
#include <Magick++.h>
#endif

namespace sani {

	namespace resource {

		Texture2DContent::Texture2DContent(const uint32 width, const uint32 height, const PixelData& pixels) : ResourceItem(), 
																											   width(width), 
																											   height(height) {
			faces.push_back(pixels);
		}

		void Texture2DContent::generateMipmaps(bool overwrite) {
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
			if (!overwrite && faces.size() > 1) return;
			if (overwrite) {
				FNCLOG_ERR(log::OutFlags::All, "not implemented");

				std::abort();
			}

			uint32 w = width;
			uint32 h = height;

			Magick::Image img;

			img.read(width, height, "RGBA", Magick::CharPixel, faces.back().data());
			// flip the buffers 
			img.flip();
			// write the flipped pixels back
			img.write(0, 0, width, height, "RGBA", Magick::CharPixel, faces.back().data());

			while (w > 1 && h > 1) {
				w /= 2;
				h /= 2;

				img.resize(Magick::Geometry(w, h));

				faces.push_back(PixelData(w * h * 4));

				img.write(0, 0, w, h, "RGBA", Magick::CharPixel, faces.back().data());
			}
#else
			FNCLOG_ERR(log::OutFlags::All, "not implemented");
			
			std::abort();
#endif
		}
		
		const std::vector<std::vector<unsigned char>>& Texture2DContent::getMipmaps() const {
			return faces;
		}
		const uint32 Texture2DContent::getWidth() const {
			return width;
		}
		const uint32 Texture2DContent::getHeight() const {
			return height;
		}
	}
}