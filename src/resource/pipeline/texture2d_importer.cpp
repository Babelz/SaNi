#include "sani/resource/pipeline/texture2d_importer.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/resource/texture2d_content.hpp"
#include <iostream>
#include <algorithm>
#include <png.h>

namespace sani {
	namespace resource {
		namespace pipeline {

			static void read(png_struct* pngStructure, unsigned char* buffer, uint32 size) {
				using namespace sani::io;
				FileStream* stream = static_cast<FileStream*>(png_get_io_ptr(pngStructure));
				stream->read(buffer, size);
			}

			static void onError(png_struct*, const char* msg) {
				// TODO LOG
				std::cerr << "PNG ERROR " << msg << std::endl;
				assert(0 && "PNG reading failed");
			}

			static void onWarning(png_struct*, const char* msg) {
				// TODO LOG
				std::cout << "PNG WARNING " << msg << std::endl;
			}

			Texture2DImporterImpl::Texture2DImporterImpl() {
				supportedFileTypes.push_back(".png");
			}

			Texture2DContent* Texture2DImporterImpl::import(const String& filename, FileSystem* fileSystem) {
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
				// TODO error reporting!!!!
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
				sani::io::FileStream* stream;
				fileSystem->openFile(filename, Filemode::Read, &stream);
				
				png_set_read_fn(pngStructure, stream, read);

				png_read_png(pngStructure,
					pngInfo,
					PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_SCALE_16,
					nullptr);
				const uint32 width = png_get_image_width(pngStructure, pngInfo);
				const uint32 height = png_get_image_height(pngStructure, pngInfo);
				const uint32 rowByteCount = png_get_rowbytes(pngStructure, pngInfo);
				Texture2DContent* txc = new Texture2DContent{
					width,
					height,
					std::vector<unsigned char>(height * rowByteCount)
				};
				txc->pixels.shrink_to_fit();
				
				
				unsigned char** rows = png_get_rows(pngStructure, pngInfo);
				for (size_t i = 0; i < height; ++i) {
					std::copy(rows[i], rows[i] + rowByteCount, txc->pixels.data() + i * rowByteCount);
				}

				png_destroy_read_struct(&pngStructure, &pngInfo, nullptr);
				return txc;
			}
		}
	}
}