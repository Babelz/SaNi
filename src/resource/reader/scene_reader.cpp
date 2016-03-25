#include "sani/engine/sani_engine.hpp"
#include "sani/resource/reader/scene_reader.hpp"
#include "sani/rtti/type_database.hpp"
#include "sani/resource/scene.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/ecs/components/transform_component.hpp"
#include "sani/rtti/argument.hpp"
#include "sani/core/logging/log.hpp"
#include <rapidjson/document.h>
#include <iostream>
#include "sani/core/utils/convert.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/services/contracts/entity_manager_contract.hpp"
#include "sani/engine/services/contracts/component_manager_contract.hpp"

namespace sani {

	namespace resource {

		namespace reader {
			
            namespace r = rapidjson;
            namespace su = sani::utils;
			namespace {
				auto &db = sani::rtti::TypeDatabase::getInstance();
#define MAKE_PAIR(type, f) { typeof(type).getID(), [](const String8& s) { return sani::rtti::Object(f(s)); }}

                static std::unordered_map<sani::rtti::TypeID, std::function<sani::rtti::Object(const String8&)>> Convertors{
                    MAKE_PAIR(float32, su::toFloat32),
                    MAKE_PAIR(int32, su::toInt32),
                    MAKE_PAIR(float64, su::toFloat64),
                    // todo add more ?
                };
#undef MAKE_PAIR
			}

			void SceneReader::RTTI_Init() {
				RTTI_REGISTER_TYPE(sani::resource::reader::ResourceTypeReader);
				RTTI_REGISTER_TYPE(sani::resource::reader::SceneReader);
				RTTI_DECLARE_BASECLASSES(sani::resource::reader::SceneReader, typeof(sani::resource::reader::ResourceTypeReader));
				RTTI_DEFAULT_DYNAMIC_CTOR(sani::resource::reader::SceneReader);
			}

			SceneReader::~SceneReader() {

			}

            void setFieldData(const sani::rtti::Type rootType, sani::rtti::Object& instance,
                r::Value::ConstMemberIterator it, r::Value::ConstMemberIterator end) {
                for (; it != end; ++it) {
                    if (it->value.IsObject()) {
                        auto& db = sani::rtti::TypeDatabase::getInstance();
                        String8 fieldName(it->name.GetString());
                        const sani::rtti::Field& field = rootType.getField(fieldName);
                        SANI_ASSERT(field.isValid());
                        sani::rtti::Type fieldType = field.getType();
                        sani::rtti::Object fieldInstance = fieldType.create(sani::rtti::Arguments{});

                        //parseComponent(it)
                        auto& obj = it->value.GetObject();
                        setFieldData(fieldType, fieldInstance, obj.MemberBegin(), obj.MemberEnd());
                        field.setValue(instance, fieldInstance);
                    }
                    else {
                        const sani::rtti::Field& field = rootType.getField(it->name.GetString());
                        const sani::rtti::Type fieldType = field.getType();
                        sani::rtti::TypeID fieldId = fieldType.getID();
#if _DEBUG
                        SANI_ASSERT(Convertors.count(fieldId));
#endif
                        auto convertor = Convertors.at(fieldId);
                        
                        field.setValue(instance, convertor(it->value.GetString()));
                        std::cout << it->name.GetString() << " = " << it->value.GetString() << std::endl;
                    }
                }
            }

            void parseComponent(r::Value::ConstValueIterator componentItr) {
                auto m = componentItr->MemberBegin();
                // the first one should be name
                String componentTypename(m->value.GetString());
                // get "transform" from "sani::Transform"
                String8 componentManagerName(componentTypename.substr(componentTypename.rfind(":") + 1) + " manager");
                std::transform(componentManagerName.begin(), componentManagerName.begin() + 1, componentManagerName.begin(), ::tolower);

                auto& db = sani::rtti::TypeDatabase::getInstance();
#if _DEBUG
                SANI_ASSERT(db.ids.count(componentTypename));
#endif
                
                sani::rtti::Type componentType = db.ids[componentTypename];
                sani::rtti::Object componentInstance = componentType.create(sani::rtti::Arguments{});
                // advance
                ++m;
                setFieldData(componentType, componentInstance, m, componentItr->MemberEnd());
                
            }

            void parseComponents(const r::Value& componentObjects) {
                for (r::Value::ConstValueIterator componentIt = componentObjects.Begin();
                    componentIt != componentObjects.End(); ++componentIt) {

                    parseComponent(componentIt);

                }
            }

            void parseEntities(const r::Value& entitesObject, engine::SaNiEngine* const engine) {
                for (r::Value::ConstValueIterator entityIt = entitesObject.Begin(); 
                    entityIt != entitesObject.End(); ++entityIt) {

                    auto createEntityMsg = engine->createEmptyMessage<messages::DocumentMessage>();
                    entitymanager::createEntity(createEntityMsg);
                    engine->routeMessage(createEntityMsg);

                    Entity* entity = static_cast<Entity*>(createEntityMsg->getData());

                    engine->releaseMessage(createEntityMsg);

                    parseComponents(entityIt->GetObject()["components"]);
                }
            }

            void parseJson(const r::Document& document, engine::SaNiEngine* const engine) {
                const r::Value& rootObject = document["scene"];
                const r::Value& entitiesObject = rootObject["entities"];
                parseEntities(entitiesObject, engine);
            }

			void* SceneReader::read(ResourceReader* reader) {
                
				Scene* scene = nullptr;

				String8 sceneName(reader->readString());
                String8 json(reader->readString());
			
                auto engine = reader->getResourceManager().getEngine();

                auto createComponentMsg = engine->createEmptyMessage<messages::DocumentMessage>();
                componentmanager::createComponent("transform manager", createComponentMsg);
                engine->routeMessage(createComponentMsg);
                Transform* tx = static_cast<Transform*>(createComponentMsg->getData());
                engine->releaseMessage(createComponentMsg);

                r::Document document;
                document.Parse<0>(json);

                parseJson(document, engine);

                
				//scene = new Scene(sceneName, filesToLoad);
				return scene;
			}
			
		}
	}
}



