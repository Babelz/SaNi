#include "sani/resource/texture2d_content.hpp"
#include <Magick++.h>
namespace sani {
	namespace resource {
		Texture2DContent::Texture2DContent(
			const uint32 width, const uint32 height, const PixelData& pixels)
			: width(width), height(height) {
			faces.push_back(pixels);
		}

		void Texture2DContent::generateMipmaps(bool overwrite) {
//			if (!overwrite && !faces.empty()) return;
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
	}
}