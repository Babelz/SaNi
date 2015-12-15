#include "sani/resource/compiler/bitmap_content_writer.hpp"
#include "sani/resource/compiler/resource_writer.hpp"
namespace sani {
	namespace resource {
		namespace compiler{
			void BitmapContentWriter::write(ResourceWriter* writer, const void* value) {
				const BitmapContent* content = static_cast<const BitmapContent*> (value);
				//writer->write(content->getWidth());
				//writer->write(content->getHeight());
				std::vector<unsigned char> pixels;
				content->getPixelData(pixels);
			}
		}
	}
}