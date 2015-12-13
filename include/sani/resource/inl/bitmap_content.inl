#include "../bitmap_content.hpp"

namespace sani {
	namespace resource {

		inline const uint32 BitmapContent::getWidth() const {
			return width;
		}

		inline const uint32 BitmapContent::getHeight() const {
			return height;
		}

		template <class PixelType>
		PixelBitmapContent<PixelType>::PixelBitmapContent(uint32 width, uint32 height) 
			: BitmapContent(width, height), pixels(new PixelType[width * height]), format(graphics::SurfaceFormat::ColorRGBA) {
			// transparent
			memset(pixels, 0, sizeof(PixelType) * width * height);
			tryGetFormat(&format);
		}

		template <class PixelType>
		PixelBitmapContent<PixelType>::~PixelBitmapContent() {
			delete[] pixels;
		}


		template <class PixelType>
		void PixelBitmapContent<PixelType>::tryGetFormat(graphics::SurfaceFormat* out) const {
			using namespace sani::math;
			using namespace sani::graphics;
			if (typeid(PixelType) == typeid(Vec4f)) {
				*out = SurfaceFormat::ColorRGBA;
			}		
		}

		template <class PixelType>
		void PixelBitmapContent<PixelType>::setPixel(uint32 index, const PixelType& value) {
			if (index >= (width * height)) throw std::runtime_error("AS");
			pixels[index] = value;
		}

	}
}