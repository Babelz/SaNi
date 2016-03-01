#include "sani/resource/reader/scene_reader.hpp"
#include "sani/rtti/type_database.hpp"

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
				return nullptr;
			}

		}
	}
}



