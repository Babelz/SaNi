#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/compiler/texture2d_writer.hpp"
#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/texture2d_content.hpp"

namespace sani {

	namespace resource {

		namespace compiler {
			
			Texture2DWriter::Texture2DWriter() : ResourceTypeWriter() {
			}

			Texture2DWriter::~Texture2DWriter() {
			}

			void Texture2DWriter::write(ResourceWriter* writer, const void* value) {
				using PixelData		= std::vector<unsigned char>;
				using MipmapChain	= std::vector < PixelData>;

				const Texture2DContent* tex = static_cast<const Texture2DContent*>(value);
				const MipmapChain& mipmaps = tex->getMipmaps();

				writer->write(tex->getWidth());
				writer->write(tex->getHeight());

				writer->write7BitEncodedInt(mipmaps.size());

				///// TODO COMPRESS ////

				for (size_t i = 0; i < mipmaps.size(); ++i) {
					const PixelData& face = mipmaps[i];
					
					// write the byte count
					writer->write7BitEncodedInt(face.size());
					for (size_t i = 0; i < face.size(); ++i) writer->write((uint8)face[i]);
				}
			}
		}
	}
}

#endif