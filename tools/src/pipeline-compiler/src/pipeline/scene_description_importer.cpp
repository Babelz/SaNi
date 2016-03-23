#include "sani/resource/pipeline/scene_description_importer.hpp"
#include "rapidjson/document.h"
#include <iostream>
#include "sani/resource/scene.hpp"
#include "sani/core/logging/log.hpp"
#include <memory>

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

                String8 json(fileSystem->getFileDataString(filename));

				fileSystem->closeFile(filename);

				Document document;
				if (document.Parse<0>(json).HasParseError()) {
                    FNCLOG_ERR(log::OutFlags::All, String8("Scene file ") + filename + String(" is not valid JSON!"));
                    std::abort();
				}

				bool isValid = 1
					&& document.HasMember("scene");

				if (!isValid) {
					FNCLOG_ERR(log::OutFlags::All, String8("Scene file ") + filename + String(" is missing scene object!"));
					std::abort();
				}
				Value& scene = document["scene"];
				isValid = scene.HasMember("name"); 
				
				if (!isValid) {
					FNCLOG_ERR(log::OutFlags::All, String8("Scene file ") + filename + String(" is missing scene attribute name!"));
					std::abort();
				}

				isValid = scene.HasMember("entities") // todo what if it's empty?
					   && scene["entities"].IsArray();

				SceneDescription* descriptor = new SceneDescription(scene["name"].GetString(), json);

			/*	for (Value::ConstValueIterator it = entities.Begin(); it != entities.End(); ++it) {
					auto& entity = it->GetObjectW();
					std::cout << "Entity has components?" << std::boolalpha << entity.HasMember("components") << std::endl;
					auto& components = entity["components"];
					std::cout << "components is array: " << std::boolalpha << components.IsArray() << std::endl;

					for (Value::ConstValueIterator componentIt = components.Begin(); componentIt != components.End(); ++componentIt) {
						auto& componentObject = componentIt->GetObjectW();
						
                        auto memberIt = componentObject.MemberBegin();

						SceneDescription::Component component;
                        component.name = memberIt->value.GetString();
                        ++memberIt;
                   
                        for (; memberIt != componentObject.MemberEnd(); ++memberIt) {
                            // it's object
                            if (memberIt->value.IsObject()) {
                                String8 fieldName(memberIt->name.GetString());
                                SceneDescription::ObjectField objField{ fieldName };
                                objField.fields.reserve(memberIt->value.MemberCount());
                                // TODO recursion?
                                for (auto it = memberIt->value.MemberBegin(); it != memberIt->value.MemberEnd(); ++it) {
                                    objField.fields.emplace_back(it->name.GetString(), it->value.GetString());
                                }
                                component.objectFields.emplace_back(objField);
                            }
                            // it's primitive
                            else {
                                component.primitiveFields.emplace_back(memberIt->name.GetString(), memberIt->value.GetString());
                            }
                        }
                        descriptor->components.emplace_back(component);
					}

				}*/
				
				return descriptor;
			}
		}
	}
}



