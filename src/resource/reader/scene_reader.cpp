#include "sani/resource/reader/scene_reader.hpp"
#include "sani/rtti/type_database.hpp"
#include "sani/resource/scene.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/ecs/components/transform_component.hpp"
#include "sani/rtti/argument.hpp"
#include "sani/core/logging/log.hpp"
#include <rapidjson/document.h>
#include <iostream>
namespace sani {

	namespace resource {

		namespace reader {
			
            namespace r = rapidjson;

			namespace {
				auto &db = sani::rtti::TypeDatabase::getInstance();
			}

			void SceneReader::RTTI_Init() {
				RTTI_REGISTER_TYPE(sani::resource::reader::ResourceTypeReader);
				RTTI_REGISTER_TYPE(sani::resource::reader::SceneReader);
				RTTI_DECLARE_BASECLASSES(sani::resource::reader::SceneReader, typeof(sani::resource::reader::ResourceTypeReader));
				RTTI_DEFAULT_DYNAMIC_CTOR(sani::resource::reader::SceneReader);
			}

			SceneReader::~SceneReader() {

			}

            void parseComponent(r::Value::ConstMemberIterator it, r::Value::ConstMemberIterator end) {
                for (it; it != end; ++it) {
                    if (it->value.IsObject()) {
                        //parseComponent(it)
                    }
                    else {
                        std::cout << it->name.GetString() << " = " << it->value.GetString() << std::endl;
                    }
                }
            }

            void parseComponent(r::Value::ConstValueIterator componentItr) {
                auto m = componentItr->MemberBegin();
                // the first one should be name
                String8 componentTypename(m->value.GetString());
                // advance
                ++m;


            }

            void parseComponents(const r::Value& componentObjects) {
                for (r::Value::ConstValueIterator componentIt = componentObjects.Begin();
                    componentIt != componentObjects.End(); ++componentIt) {

                    parseComponent(componentIt);

                }
            }

            void parseEntities(const r::Value& entitesObject) {
                for (r::Value::ConstValueIterator entityIt = entitesObject.Begin(); 
                    entityIt != entitesObject.End(); ++entityIt) {
                    parseComponents(entityIt->GetObject()["components"]);
                }
            }

            void parseJson(const r::Document& document) {
                const r::Value& rootObject = document["scene"];
                const r::Value& entitiesObject = rootObject["entities"];
                parseEntities(entitiesObject);
            }

			void* SceneReader::read(ResourceReader* reader) {
                
				Scene* scene = nullptr;

				String8 sceneName(reader->readString());
                String8 json(reader->readString());
			
                r::Document document;
                document.Parse<0>(json);

                parseJson(document);
				//scene = new Scene(sceneName, filesToLoad);
				return scene;
			}
			
		}
	}
}



