#pragma once
#include "sani/resource/pipeline/content_importer.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/platform/file/file_system.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

#include <png.h>
// TODO move this
// http://stackoverflow.com/questions/11296644/loading-png-textures-to-opengl-with-libpng-only
void read(png_struct* pngStructure, unsigned char* buffer, uint32 size);
struct Test {
	sani::io::FileSystem* fs;
	String filename;
};
namespace sani {
	using namespace io;
	namespace resource {
		namespace pipeline {
			class Texture2DImporterImpl {
			private:
				std::vector<String> supportedFileTypes;
			public:
				Texture2DImporterImpl() {
					supportedFileTypes.push_back(".png");
				}
				~Texture2DImporterImpl() = default;
				Texture2D* import(const String& filename, FileSystem* fileSystem) {
					std::cout << "Texture2DImporterImpl::import(String&) invoked" << std::endl;
					size_t index = filename.rfind(".");
					if (index == String::npos) {
						throw std::runtime_error("Couldnt determine the file type!");
					}
					String extension(filename.substr(index));
					// if the extension isnt supported
					if (std::find(supportedFileTypes.begin(), supportedFileTypes.end(), extension) == supportedFileTypes.end()) {
						throw std::runtime_error("File extension isnt supported!");
					}

					png_structp pngStructure = png_create_read_struct(
						PNG_LIBPNG_VER_STRING,
						nullptr, // error struct
						nullptr, // error func
						nullptr); // warning

					if (pngStructure == nullptr) {
						throw std::runtime_error("Failed to initialize png read struct");
					}

					png_infop pngInfo = png_create_info_struct(pngStructure);
					if (pngInfo == nullptr) {
						throw std::runtime_error("Failed to initialize png info struct");
					}
					fileSystem->openFile(filename, Filemode::Read);
					Test asd{ fileSystem, filename };
					png_set_read_fn(pngStructure, &asd, read);
					
					png_read_png(pngStructure, 
						pngInfo, 
						PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_SCALE_16, 
						nullptr);

					const uint32 height = png_get_image_height(pngStructure, pngInfo);
					const uint32 rowByteCount = png_get_rowbytes(pngStructure, pngInfo);
					std::vector<unsigned char> pixels(height * rowByteCount);
					pixels.shrink_to_fit();
					unsigned char** rows = png_get_rows(pngStructure, pngInfo);
					for (size_t i = 0; i < height; ++i) {
						std::copy(rows[i], rows[i] + rowByteCount, pixels.data() + i * rowByteCount);
					}
					return nullptr;
				}
			};
			typedef ContentImporter<Texture2D, Texture2DImporterImpl> Texture2DImporter;
		}
	}
}

void read(png_struct* pngStructure, unsigned char* buffer, uint32 size) {
	using namespace sani::io;
	Test* test = static_cast<Test*>(png_get_io_ptr(pngStructure));
	test->fs->readBytes(test->filename, buffer, size);
}