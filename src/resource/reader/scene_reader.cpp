#include "sani/resource/reader/scene_reader.hpp"
#include "sani/rtti/type_database.hpp"
#include "sani/resource/scene.hpp"
#include "sani/resource/reader/resource_reader.hpp"

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
				scene = new Scene(sceneName, filesToLoad);
				return scene;
			}
			
		}
	}
}



