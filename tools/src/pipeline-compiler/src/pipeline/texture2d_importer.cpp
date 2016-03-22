#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "sani/resource/pipeline/texture2d_importer.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/resource/texture2d_content.hpp"
#include "sani/debug.hpp"
#include <iostream>
#include <algorithm>
#include <Magick++.h>

namespace sani {

	namespace resource {

		namespace pipeline {

			Texture2DImporter::Texture2DImporter() : ContentImporter() {
				supportedFileTypes.push_back(".png");
			}
			Texture2DImporter::~Texture2DImporter() { 
			}

			ResourceItem* Texture2DImporter::import(const String& filename, FileSystem* fileSystem) const {
				const size_t index = filename.rfind(".");
				if (index == String::npos) {
					throw std::runtime_error("Couldn't determine the file type!");
				}

				String extension(filename.substr(index));
				// if the extension isn't supported
				if (std::find(supportedFileTypes.begin(), supportedFileTypes.end(), extension) == supportedFileTypes.end()) {
					throw std::runtime_error("File extension isn't supported!");
				}

				Magick::Image img;
				img.read(filename);
				
				const size_t w = img.columns();
				const size_t h = img.rows();
			
				std::vector<unsigned char> pixels(w * h * 4);
				img.write(0, 0, w, h, "RGBA", Magick::CharPixel, pixels.data());

				Texture2DContent* txc = new Texture2DContent(w, h, pixels);
				
				return txc;
			}
		}
	}
}

#endif