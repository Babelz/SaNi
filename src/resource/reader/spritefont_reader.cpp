#include "sani/resource/reader/resource_reader.hpp"
#include "sani/resource/reader/spritefont_reader.hpp"
#include "sani/resource/bitmap_content.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			SpriteFontReader::SpriteFontReader() {}

			SpriteFontReader::~SpriteFontReader() {}

			void* SpriteFontReader::read(ResourceReader* reader) {
				BitmapContent* texture = reader->readObject<BitmapContent>();

				return nullptr;
			}
		}
	}
}
