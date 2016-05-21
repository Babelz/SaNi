#include "sani/resource/pipeline/scene_description_importer.hpp"
#include "rapidjson/document.h"
#include <iostream>
#include "sani/resource/scene.hpp"
#include "sani/core/logging/log.hpp"
#include <memory>
#include "sani/debug.hpp"

namespace sani {
	namespace resource {
		namespace pipeline {

			SceneDescriptionImporter::SceneDescriptionImporter() {

			}

			SceneDescriptionImporter::~SceneDescriptionImporter() {

			}

            void processEntity(io::FileSystem* fileSystem, const String8& root, const String8& name, rapidjson::Value& v) {
                static const char Extension[] = ".entity";

                const uint32_t MaxPrefabs = 2;
                rapidjson::Value prefabs[MaxPrefabs];
                rapidjson::Document docs[MaxPrefabs - 1];
                prefabs[0] = v;
                // itself 
                uint32_t numPrefabs = 1;
                
                for (uint32_t i = 0; i < MaxPrefabs; ++i, ++numPrefabs) {

                    const rapidjson::Value& prefab = prefabs[i];
                    // we must go deeper ":D"
                    if (!prefab.HasMember("prefab")) {
                        break;
                    }

                    String8 path(root + prefab["prefab"].GetString());
                    path += Extension;
                    io::FileStream* file;
                    if (!fileSystem->openFile(path, io::Filemode::Read, &file)) {
                        std::cerr << "Failed to prefab file: " << path << std::endl;
                        std::abort();
                    }
                    String8 prefabJson(fileSystem->getFileDataString(path));
                    docs[i].Parse(prefabJson);
                    fileSystem->closeFile(path);
                    prefabs[i + 1] = docs[i].GetObjectW();
                }

                rapidjson::Value& prefabObject = prefabs[numPrefabs - 1];
                rapidjson::Value& prefabComponents = prefabObject["components"];
                
                // merge prefab components to actual entity json
                if (numPrefabs > 1) {

                    for (uint32_t i = 0; i < numPrefabs; ++i) {
                        // from last to first
                        rapidjson::Value& prefab = prefabs[numPrefabs - i - 1];
                        // this prefab doesn't have any overrided components
                        if (!prefab.HasMember("override")) continue;

                        rapidjson::Value& overridedComponents = prefab["override"];

                    }
                }

            }

			ResourceItem* SceneDescriptionImporter::import(const String& filename, io::FileSystem* fileSystem) const {
				using namespace sani::io;
				using namespace rapidjson;
				FileStream* stream = nullptr;
				fileSystem->openFile(filename, Filemode::Read, &stream);

                String8 json(fileSystem->getFileDataString(filename));

				fileSystem->closeFile(filename);

                const String root(filename.substr(0, filename.rfind("\\") + 1));

				Document document;
				if (document.Parse<0>(json).HasParseError()) {
                    FNCLOG_ERR(log::OutFlags::All, String8("Scene file ") + filename + String(" is not valid JSON!"));
                    std::abort();
				}

				bool isValid = 1
					&& document.HasMember("entities"); // every scene needs at least entities (can be empty) 

				if (!isValid) {
					FNCLOG_ERR(log::OutFlags::All, String8("Scene file ") + filename + String(" is missing entites!"));
					std::abort();
				}

                isValid = document["entities"].IsObject();

                if (!isValid) {
                    FNCLOG_ERR(log::OutFlags::All, String8("Entities file ") + filename + String(": Entities isn't object"));
                    std::abort();
                }

                Value& entities = document["entities"];
               
                auto entitiesBegin = entities.MemberBegin();
                auto entitiesEnd = entities.MemberEnd();

                for (auto it = entitiesBegin; it != entitiesEnd; ++it) {
                    processEntity(fileSystem, root, it->name.GetString(), it->value);
                }

                SceneDescription* descriptor = new SceneDescription(json);

				
				return descriptor;
			}
		}
	}
}



