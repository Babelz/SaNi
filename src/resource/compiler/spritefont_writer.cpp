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

				typedef std::vector<unsigned short> Characters;
				typedef std::vector<math::Recti> Glyphs;
								
				const Glyphs& glyphs = content->getGlyphs();
				// write sources
				writer->write7BitEncodedInt(glyphs.size());
				
				for (const auto& rect : glyphs) {
					// TODO create writer for this
					writer->write(rect.x);
					writer->write(rect.y);
					writer->write(rect.w);
					writer->write(rect.h);
				}

				const Characters& characters = content->getCharacters();
				// write characters
				writer->write7BitEncodedInt(characters.size());
				for (unsigned short ch : characters) {
					writer->write(ch);
				}
			}
		}
	}
}