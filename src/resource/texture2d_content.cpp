#include "sani/resource/texture2d_content.hpp"
#include <Magick++.h>
namespace sani {
	namespace resource {
		Texture2DContent::Texture2DContent(
			const uint32 width, const uint32 height, const PixelData& pixels)
			: ResourceItem(), width(width), height(height) {
			faces.push_back(pixels);
		}

		void Texture2DContent::generateMipmaps(bool overwrite) {
			if (!overwrite && faces.size() > 1) return;
			if (overwrite) throw std::logic_error("not implemented");
			uint32 w = width;
			uint32 h = height;

			Magick::Image img;
			img.magick("PNG");
			img.read(width, height, "RGBA", Magick::CharPixel, faces[0].data());

			
			while (w > 1 && h > 1) {
				w /= 2;
				h /= 2;
				img.resize(Magick::Geometry(width, height));
				faces.push_back(PixelData(w * h * 4));
				img.write(0, 0, w, h, "RGBA", Magick::CharPixel, faces[faces.size() - 1].data());
			}
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