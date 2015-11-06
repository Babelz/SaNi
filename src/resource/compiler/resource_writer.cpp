#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/platform/file/file_stream.hpp"
#include "sani/resource/compiler/resource_compiler.hpp"

namespace sani {
	using namespace io;
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

			ResourceWriter::ResourceWriter(const FileStream* stream, const ResourceCompiler* compiler) 
				: BinaryWriter(stream), compiler(compiler) {

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

			void ResourceWriter::writeTypeWriters() {
				write7BitEncodedInt(writers.size());
				for (auto& kv : writers) {
					write(kv.second->getRuntimeReader());
				}
			}
		}
	}
}