#include "sani/resource/pipeline/scene_description_importer.hpp"
#include "rapidjson/document.h"
#include <iostream>
#include "sani/resource/scene.hpp"

namespace sani {
	namespace resource {
		namespace pipeline {

			SceneDescriptionImporter::SceneDescriptionImporter() {

			}

			SceneDescriptionImporter::~SceneDescriptionImporter() {

			}

			ResourceItem* SceneDescriptionImporter::import(const String& filename, io::FileSystem* fileSystem) const {
				using namespace sani::io;
				using namespace rapidjson;
				FileStream* stream = nullptr;
				fileSystem->openFile(filename, Filemode::Read, &stream);

				int64 length = 0;
				char* json = (char*)fileSystem->getFileData(filename, length, true);

				fileSystem->closeFile(filename);

				Document document;
				if (document.ParseInsitu(json).HasParseError()) {
					throw std::runtime_error("Scene file is invalid!");
				}

				std::cout << "Has member scene: " << std::boolalpha << document.HasMember("scene") << std::endl;
				Value& scene = document["scene"];
				
				std::cout << "Has member name: " << std::boolalpha << scene.HasMember("name") << std::endl;
				SceneDescription* descriptor = new SceneDescription(scene["name"].GetString());

				std::cout << "Has member folders: " << std::boolalpha << scene.HasMember("folders") << std::endl;

				if (scene.HasMember("folders")) {
					Value& folders = scene["folders"];
					std::cout << "folders is array?: " << std::boolalpha << folders.IsArray() << std::endl;

					for (Value::ConstValueIterator it = folders.Begin(); it != folders.End(); ++it) {
						auto& folder = it->GetObjectW();
						uint32 id = folder["id"].GetUint();
						String8 folderName(folder.HasMember("name") ? folder["name"].GetString() : "");
						AssetFolder f{ id, folderName };

						descriptor->addFolder(f);
						auto& assets = folder["assets"];
						for (Value::ConstValueIterator assetIt = assets.Begin(); assetIt != assets.End(); ++assetIt) {
							auto& asset = assetIt->GetObjectW();
							// TODO move semantics?
							descriptor->addAssetTo(f, AssetFile{ asset["id"].GetUint(), asset["name"].GetString()});
						}
					}
				}

				std::cout << "Scene has member entities: " << std::boolalpha << scene.HasMember("entities") << std::endl;
				auto& entities = scene["entities"];
				std::cout << "Entities is array: " << std::boolalpha << entities.IsArray() << std::endl;

				for (Value::ConstValueIterator it = entities.Begin(); it != entities.End(); ++it) {
					auto& entity = it->GetObjectW();
					std::cout << "Entity has componens?" << std::boolalpha << entity.HasMember("components") << std::endl;
					auto& components = entity["components"];
					std::cout << "components is array: " << std::boolalpha << components.IsArray() << std::endl;

					for (Value::ConstValueIterator componentIt = components.Begin(); 
						componentIt != components.End();
						++componentIt) {
						auto& component = componentIt->GetObjectW();
						std::cout << "component.name = " << component["name"].GetString() << std::endl;
						
						auto& fields = component["fields"];
						for (Value::ConstValueIterator fieldIt = fields.Begin();
							fieldIt != fields.End();
							++fieldIt) {
							auto& field = fieldIt->GetObjectW();
							std::cout << field["name"].GetString() << " = " << field["value"].GetString() << std::endl;
						}
					}
				}

				return descriptor;
			}
		}
	}
}



