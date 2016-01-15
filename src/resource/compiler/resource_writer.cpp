#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

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

			ResourceWriter::ResourceWriter(FileStream* fileStream, const ResourceCompiler* compiler)
				: BinaryWriter(&memoryStream), compiler(compiler), fileStream(fileStream) {

			}

			ResourceWriter::~ResourceWriter() {}

			void ResourceWriter::writeHeader() {
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_UNKOWN
#error "Couldnt determine the platform"
#endif
				// magic 3 bytes
				write((uint8)'S');
				write((uint8)'N');
				write((uint8)'B');

				// platform
				write((uint8)Platforms[SANI_TARGET_PLATFORM]);
				// version, is this needed?
				write(Version);
			}

			void ResourceWriter::writeTypeWriters() {
				write7BitEncodedInt(writers.size());

				for (auto& kv : writers) {
					write(kv.second->getRuntimeReader());
				}
			}

			ResourceTypeWriter* ResourceWriter::getWriter(const std::type_index& info) {
				// we dont have writer yet lets add it
				if (writers.find(info) == writers.end()) {
					ResourceTypeWriter* w = compiler->getWriter(info);
					writers[info] = w;
					return w;
				}

				// we have the typewriter already
				return writers[info];
			}

			void ResourceWriter::writeObject(const std::type_index& type, const ResourceItem* obj) {
				if (obj == nullptr) {
					throw std::runtime_error("obj is nullptr");
				}

				ResourceTypeWriter* writer = getWriter(type);
				if (writer == nullptr) {
					throw std::runtime_error("Cant get writer for T");
				}

				write7BitEncodedInt(std::distance(writers.begin(), writers.find(type)));
				writer->write(this, obj);
			}

			void ResourceWriter::flush(const std::type_index& type, const ResourceItem* obj) {
				// write the final object..
				writeObject(type, obj);

				// swap the stream now
				Stream* currentStream = stream;
				stream = fileStream;

				// we are writing now to file so
				// 1) the object has wrote all the type readers
				// 2) memory stream has all data from object
				// 3) we need to get the data from stream

				// write the header..
				writeHeader();
				// write the readers to deserialize
				writeTypeWriters();

				int64 memorySize = memoryStream.size();

				std::vector<unsigned char> buffer;
				buffer.resize(memorySize);

				memoryStream.seek(SeekPosition::Begin, 0);

				memoryStream.read(buffer.data(), memorySize);
				fileStream->write(buffer.data(), memorySize);

				BinaryWriter::flush();
			}
		}
	}
}

#endif