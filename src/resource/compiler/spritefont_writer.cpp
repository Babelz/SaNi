#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/compiler/spritefont_writer.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/resource/texture2d_content.hpp"
#include "sani/resource/bitmap_content.hpp"
#include "sani/resource/texture2d.hpp"

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

				// TODO demo hax
				BitmapContent* texture = content->getTexture();
				std::vector<unsigned char> pixels;
				pixels.reserve(texture->getWidth() * texture->getHeight() * sizeof(math::Vector4<unsigned char>));
				texture->getPixelData(pixels);
				Texture2DContent texcontent(texture->getWidth(), texture->getHeight(), pixels);
				// TODO this should be texture...
				writer->writeObject(std::type_index(typeid(Texture2DContent)), &texcontent);
			}
		}
	}
}