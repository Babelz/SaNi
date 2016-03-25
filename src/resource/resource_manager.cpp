#include "sani/resource/resource_manager.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/resource/resource.hpp"
#include "sani/core/logging/log.hpp"
#include "sani/engine/sani_engine.hpp"
#include <sstream>

namespace sani {

	namespace resource {

		ResourceManager::ResourceManager(FileSystem* fileSystem, GraphicsDevice* gdevice, 
										 engine::SaNiEngine* const engine, String8& root) : fileSystem(fileSystem), 
																					 graphicsDevice(gdevice),
																					 contentRoot(root),
                                                                                     engine(engine) {
			// get rid of path separator
			std::size_t index = contentRoot.rfind("/", contentRoot.length() - 1);
			if (index != std::string::npos) {
				contentRoot.erase(index, 1);
			}
			typeReaders.registerStandardTypes();
		}

		void* ResourceManager::load(const String& assetName) {
			const String8 asset(contentRoot + "/" + assetName);
			if (resources.find(asset) != resources.end()) return resources[asset];

			const String8 assetPath(asset + ".snb");

			using namespace reader;

			FileStream* stream;

			if (!fileSystem->openFile(assetPath, Filemode::Read, &stream)) {
				std::stringstream ss;
				ss << "file ";
				ss << "\"";
				ss << assetPath;
				ss << "\" ";
				ss << "not found";

				FNCLOG_ERR(log::OutFlags::All, ss.str());

				std::abort();
			}

            ResourceReader reader(stream, *this, graphicsDevice);

            void* resource = reader.readAsset(typeReaders);

            fileSystem->closeFile(asset);

            resources[asset] = static_cast<Resource*>(resource);

            return resource;
		}

        engine::SaNiEngine* const ResourceManager::getEngine() const {
            return engine;
        }

        void ResourceManager::unload() {
			// TODO ref counting?
			for (auto& kvp : resources) {
				delete kvp.second;
			}
			resources.clear();
		}
	}
}