#include "sani/resource/reader/texture2d_reader.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/resource/texture2d.hpp"
// TODO move this
#include "GL\glew.h"

namespace sani {
	namespace resource {
		namespace reader {
			Texture2DReader::~Texture2DReader() {}

			void* Texture2DReader::read(ResourceReader* reader) {
				using namespace sani::graphics;

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

				GraphicsDevice* device = reader->getGraphicsDevice();
				
				// TODO move impl to graphicsdevice
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


				uint32 w = width, h = height;

				for (size_t level = 0; level < faceCount; ++level) {
					glTexImage2D(
						GL_TEXTURE_2D,
						static_cast<GLint>(level), // mipmap lvl
						GL_RGBA,
						w,
						h,
						0,
						GL_RGBA,
						GL_UNSIGNED_BYTE,
						faces[level].data()
						);
					w /= 2;
					h /= 2;
				}
				glBindTexture(GL_TEXTURE_2D, 0);

				Texture2D* out = new Texture2D(device, width, height, texture);

				return out;
			}
		}
	}
}