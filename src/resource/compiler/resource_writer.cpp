#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/platform/platform_config.hpp"
namespace sani {
	namespace resource {
		namespace compiler {
			// DO NOT CHANGE THESE, THEY ARE FOLLOWING THE PLATFORM CONFIG
			const char ResourceWriter::Platforms[] = {
				'w', // win32
				'l', // linux
				'X', // MAC
				'a', // android
				'W', // windows phone
				'i' // iOS
				// TODO emscripte, ps4, xbox
			};

			ResourceWriter::ResourceWriter(FILE* file) 
				: BinaryWriter(file) {

			}
			ResourceWriter::~ResourceWriter() {}

			void ResourceWriter::writeHeader() {
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_UNKOWN
#error "Couldnt determine the platform"
#endif
				// magic 3 bytes
				write('S');
				write('N');
				write('B');

				// platform
				write(Platforms[SANI_TARGET_PLATFORM]);
				// version, is this needed?
				write(Version);
			}
		}
	}
}