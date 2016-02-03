#include "sani/resource/reader/texture2d_reader.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/resource/texture2d.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			Texture2DReader::~Texture2DReader() {
			}

			void* Texture2DReader::read(ResourceReader* reader) {
				using namespace sani::graphics;

				using PixelData		= std::vector<unsigned char>;
				using MipmapChain	= std::vector <PixelData>;

				const uint32 width = reader->readUint32();
				const uint32 height = reader->readUint32();
				const uint64 faceCount = reader->read7BitEncodedInt();

				// read all the faces, the largest one is stored as first
				MipmapChain faces;
				for (size_t i = 0; i < faceCount; ++i) {
					// read the byte count
					uint32 bytes = static_cast<uint32>(reader->read7BitEncodedInt());

					// alloc vector & read the pixels
					faces.push_back(PixelData(bytes));
					
					PixelData& data = faces[i];
					for (size_t j = 0; j < bytes; ++j) data[j] = reader->readByte();
				}

				GraphicsDevice* device = reader->getGraphicsDevice();

				Texture2D* out = new Texture2D(device, width, height, faceCount > 1, SurfaceFormat::ColorRGBA);

				for (size_t level = 0; level < faceCount; ++level) out->setData(device, level, nullptr, faces[level], 0, faces.size());
				
				return out;
			}
		}
	}
}