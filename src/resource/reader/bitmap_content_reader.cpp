#include "sani/resource/reader/bitmap_content_reader.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/core/math/vector.hpp"
#include "sani/resource/bitmap_content.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			BitmapContentReader::~BitmapContentReader() {
			}

			void* BitmapContentReader::read(ResourceReader* reader) {
				const uint32 width = reader->readUint32();
				const uint32 height = reader->readUint32();

				const uint32 pixelCount = static_cast<uint32>(reader->read7BitEncodedInt());
				std::vector<unsigned char> pixels(pixelCount);

				for (uint32 i = 0; i < pixelCount; ++i) pixels[i] = reader->readByte();

				using namespace sani::math;

				using Pixel = Vector4<unsigned char>;
				using Image = PixelBitmapContent<Pixel>;

				Image* image = new Image(width, height);
				image->setPixelData(pixels);

				return image;
			}
		}
	}
}