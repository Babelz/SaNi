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
			: BitmapContent(width, height), pixels(new PixelType[width * height]) {
			tryGetFormat(format);
		}

		template <class PixelType>
		PixelBitmapContent<PixelType>::~PixelBitmapContent() {
			delete[] pixels;
		}


		template <class PixelType>
		void PixelBitmapContent<PixelType>::tryGetFormat(graphics::SurfaceFormat* out) const {
			using namespace sani::math;
			out = nullptr;
			if (typeid(PixelType) == typeid(Vec4f)) {
				*out = SurfaceFormat::ColorRGBA;
			}
				
		}




	}
}