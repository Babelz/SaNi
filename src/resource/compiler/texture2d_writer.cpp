#include "sani/resource/compiler/texture2d_writer.hpp"
#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/texture2d_content.hpp"
namespace sani {
	namespace resource {
		namespace compiler {
			
			void Texture2DWriter::write(ResourceWriter* writer, void* value) {

				typedef std::vector<unsigned char> PixelData;
				typedef std::vector < PixelData> MipmapChain;
				Texture2DContent* tex = static_cast<Texture2DContent*>(value);
				const MipmapChain& mipmaps = tex->getMipmaps();
				writer->write(tex->getWidth());
				writer->write(tex->getHeight());
				writer->write7BitEncodedInt(mipmaps.size());

				///// TODO COMPRESS ////

				for (size_t i = 0; i < mipmaps.size(); ++i) {
					const PixelData& face = mipmaps[i];
					// write the byte count
					writer->write7BitEncodedInt(face.size());
					writer->writeContainer(face);
				}
				
			}
		}
	}
}