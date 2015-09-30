#include "sani/resource/resource_manager.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/resource/reader/resource_reader.hpp"
namespace sani {
	namespace resource {
		ResourceManager::ResourceManager(FileSystem* fileSystem, GraphicsDevice* gdevice)
			: fileSystem(fileSystem), graphicsDevice(gdevice) {
			typeReaders.registerStandardTypes();
		}

		void* ResourceManager::load(const String& asset) {
			if (resources.find(asset) != resources.end()) return resources[asset];

			using namespace reader;
			if (!fileSystem->openFile(asset, Filemode::Read)) {
				throw std::runtime_error("File not found!");
			}
			
			try {
				ResourceReader reader(fileSystem, asset, *this, graphicsDevice);
				void* asset = reader.readAsset(typeReaders);
			}
			catch (const std::exception& ex) {
				(void)ex;
			}
			return nullptr;
		}
	}
}