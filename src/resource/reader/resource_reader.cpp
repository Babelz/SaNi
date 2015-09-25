#include "sani/resource/reader/resource_reader.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			ResourceReader::ResourceReader(const FileSystem* fs,
				const String& file, ResourceManager& manager, GraphicsDevice* device)
				: BinaryReader(fs, file), manager(manager), graphicsDevice(device) {

			}

			ResourceReader::~ResourceReader(){}

			ResourceManager& ResourceReader::getResourceManager() const {
				return manager;
			}

			GraphicsDevice* ResourceReader::getGraphicsDevice() const {
				return graphicsDevice;
			}
		}
	}
}