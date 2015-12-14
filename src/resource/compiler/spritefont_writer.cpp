#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/compiler/spritefont_writer.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/resource/texture2d_content.hpp"
#include "sani/resource/bitmap_content.hpp"

namespace sani {
	namespace resource {
		namespace compiler {

			SpriteFontWriter::SpriteFontWriter() 
				: ResourceTypeWriter() {

			}

			SpriteFontWriter::~SpriteFontWriter() { }

			String SpriteFontWriter::getRuntimeReader() const {
				return DeserializableWith<SpriteFontContent>::value();
			}

			void SpriteFontWriter::write(ResourceWriter* writer, const void* value) {
				const SpriteFontContent* content = static_cast<const SpriteFontContent*>(value);

				// TODO this should be texture...
				writer->writeObject(std::type_index(typeid(BitmapContent)), content->getTexture());
			}
		}
	}
}