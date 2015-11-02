#include "sani/resource/reader/texture2d_reader.hpp"
#include "sani/resource/reader/resource_reader.hpp"
namespace sani {
	namespace resource {
		namespace reader {
			void Texture2DReader::read(ResourceReader* reader) {
				typedef std::vector<unsigned char> PixelData;
				typedef std::vector < PixelData> MipmapChain;

				const uint32 width = reader->readUint32();
				const uint32 height = reader->readUint32();
				const uint64 faceCount = reader->read7BitEncodedInt();

				////////////////// TODO COMPRESSION /////////////

				// read all the faces, the largest one is stored as first
				MipmapChain faces;
				for (size_t i = 0; i < faceCount; ++i) {
					// read the byte count
					uint32 bytes = static_cast<uint32>(reader->read7BitEncodedInt());
					// alloc vector & read the pixels
					faces.push_back(PixelData(bytes));
					faces.reserve(bytes);
					PixelData& data = faces[i];
					// TODO do readContainer or something
					for (size_t j = 0; j < bytes; ++j) {
						data[j] = reader->readByte();
					}
				}
			}
		}
	}
}