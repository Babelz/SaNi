#include "sani/resource/reader/scene_reader.hpp"
#include "sani/rtti/type_database.hpp"
#include "sani/resource/scene.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/ecs/components/transform_component.hpp"
#include "sani/rtti/argument.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			
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

			void* SceneReader::read(ResourceReader* reader) {
				Scene* scene = nullptr;

				String8 sceneName(reader->readString());
				
				Scene::Assets filesToLoad;
				uint32 folderCount = static_cast<uint32>(reader->read7BitEncodedInt());
				filesToLoad.reserve(folderCount);

				for (auto i = 0u; i < folderCount; ++i) {
					String8 root(reader->readString());
					auto fileCount = reader->read7BitEncodedInt();
					for (auto fileId = 0u; fileId < fileCount; ++fileId) {
						filesToLoad.emplace_back(root + reader->readString());
					}
				}

                uint64 componentCount = reader->read7BitEncodedInt();

                auto& db = sani::rtti::TypeDatabase::getInstance();

                
                sani::rtti::Type ourType = typeof(sani::Transform);
                sani::rtti::Object tx = ourType.create(sani::rtti::Arguments{});
                
                for (uint64 i = 0u; i < componentCount; ++i) {
                    uint64 objFieldCount = reader->read7BitEncodedInt();
                    for (uint64 fieldIndex = 0u; fieldIndex < objFieldCount; ++fieldIndex) {
                        String8 fieldName(reader->readString());
                        const sani::rtti::Field& objField = ourType.getField(fieldName);
                        const sani::rtti::Type objFieldType = objField.getType();
                        sani::rtti::Object instance = objFieldType.create(sani::rtti::Arguments{});
                        uint64 something = reader->read7BitEncodedInt();
                        for (uint64 gg = 0u; gg < something; ++gg) {
                            String8 name(reader->readString());
                            const sani::rtti::Field& valueField = objFieldType.getField(name);
                            uint32 type = reader->readInt32();
                            if (type == typeof(float32).getID()) {
                                // hax
                                float32 data = reader->readSingle();
                                valueField.setValue(instance, data);
                            }
                            else {
                                throw std::runtime_error("not impl");
                            }
                            
                        }
                        SANI_ASSERT(objField.setValue(tx, instance));
                    }
                }

				scene = new Scene(sceneName, filesToLoad);
				return scene;
			}
			
		}
	}
}



