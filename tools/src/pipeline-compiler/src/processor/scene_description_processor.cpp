#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/processor/scene_description_processor.hpp"
#include "sani/resource/scene.hpp"
#include "sani/rtti/type_database.hpp"
#include "sani/rtti/type.hpp"
#include "sani/debug.hpp"

namespace sani {
	namespace resource {
		namespace processor {

			ResourceItem* SceneDescriptionProcessor::process(ResourceItem* input) {
				using namespace rtti;
				auto content = static_cast<SceneDescription*>(input);
				// lets map the types
				auto& components = content->components;
				auto& db = TypeDatabase::getInstance();
				
				for (auto& componentData : components) {
					// do we even have the type
					SANI_ASSERT(db.ids.count(componentData.name));

					TypeID id = db.ids[componentData.name];
					Type componentType{ id };
					
					for (auto& fieldData : componentData.fields) {
						auto& field = componentType.getField(fieldData.name);
						// do we even have that field?
						SANI_ASSERT(field.isValid());
						Type fieldType = field.getType();
						// now we need to figure out the inner types of the field if there's any
						auto& innerType = db.types[fieldType];
					}
					// TODO type id to another type id conversion
				}

				return input;
			}

		}
	}
}

#endif



