#include "sani/resource/reader/resource_reader.hpp"
#include "sani/platform/file/file_stream.hpp"
#include "sani/resource/reader/resource_type_reader.hpp"
namespace sani {
	namespace resource {
		namespace reader {
			ResourceReader::ResourceReader(FileStream* stream,
				ResourceManager& manager, GraphicsDevice* device)
				: BinaryReader(stream), manager(manager), graphicsDevice(device) {

			}

			ResourceReader::~ResourceReader(){}

			ResourceManager& ResourceReader::getResourceManager() const {
				return manager;
			}

			GraphicsDevice* ResourceReader::getGraphicsDevice() const {
				return graphicsDevice;
			}

			void* ResourceReader::readAsset(const ResoureTypeReaderManager& typeReaders) {
				// Ensure its SNB file
				char magic[4] = { 0 };
				magic[0] = readByte();
				magic[1] = readByte();
				magic[2] = readByte();
				if (strcmp(magic, "SNB") != 0) {
					throw std::runtime_error("Not SNB file!");
				}

				// read platform
				// TODO WHY?
				readByte();
				// read version
				// TODO WHY?
				readByte();

				// type readers are initialized, get the list of used type readers
				// read the count of type readers
				uint32 typeReaderCount = static_cast<uint32>(read7BitEncodedInt());
				// TODO can there be more than 1?
				// at least now there cant be...

				std::vector<ResourceTypeReader*> readers;
				readers.reserve(typeReaderCount);

				// read the strings
				for (size_t i = 0; i < typeReaderCount; ++i) {
					String typeReaderName = readString();
					// get the type reader from manager and append it to our list
					ResourceTypeReader* reader = typeReaders.getReaderByName(typeReaderName);
					if (reader == nullptr) {
						throw std::runtime_error(String("No reader for ") + typeReaderName);
					}
					readers.push_back(reader);
				}
				uint32 index = read7BitEncodedInt();
				// TODO because there is only 1 reader atm we just assume it exist, FIX ME
				// TODO should this be fixed?
				return (*readers[index]).read((this));
			}

		}
	}
}