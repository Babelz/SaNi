#include "sani/resource/reader/scene_reader.hpp"
#include "sani/rtti/type_database.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			
			namespace {
				auto &db = sani::rtti::TypeDatabase::getInstance();

				struct ReflectionInjector {
					ReflectionInjector() {
						RTTI_REGISTER_TYPE(ResourceTypeReader);
						RTTI_REGISTER_TYPE(SceneReader);
						RTTI_DECLARE_BASECLASSES(SceneReader, typeof(ResourceTypeReader));
						RTTI_DEFAULT_DYNAMIC_CTOR(SceneReader);
					}
				};

				static ReflectionInjector ignoreme;
			}
			SceneReader::~SceneReader() {

			}

			void* SceneReader::read(ResourceReader* reader) {
				return nullptr;
			}

		}
	}
}



