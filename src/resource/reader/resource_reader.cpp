#include "sani/resource/reader/resource_reader.hpp"
#include "sani/platform/file/file_stream.hpp"
namespace sani {
	namespace resource {
		namespace reader {
			ResourceReader::ResourceReader(const FileStream* stream,
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

			void* ResourceReader::readAsset(const ResoureTypeReaderManager& typeReaders) const {
				// Ensure its SNB file
				char magic[3];
				magic[0] = readChar();
				// type readers are initialized, get the list of used type readers
				return nullptr;
			}

		}
	}
}