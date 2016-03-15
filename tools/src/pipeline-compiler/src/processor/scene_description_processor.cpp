#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/processor/scene_description_processor.hpp"
#include "sani/resource/scene.hpp"
#include "sani/rtti/type_database.hpp"
#include "sani/rtti/type.hpp"
#include "sani/debug.hpp"
#include <algorithm>
#include <iostream>

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
					
					for (auto& objectFieldData : componentData.objectFields) {
                        auto& field = componentType.getField(objectFieldData.name);
						// do we even have that field?
						SANI_ASSERT(field.isValid());
						Type fieldType = field.getType();
						// now we need to figure out the inner types of the field if there's any
						auto& fields = fieldType.getFields();

                        auto& fieldsToSearch = objectFieldData.fields;
						for (auto& candidate : fieldsToSearch) {
							String8 fieldName(candidate.name);
							auto search = std::find_if(std::begin(fields), std::end(fields), [&fieldName](const Field& field) {
								return field.getName() == fieldName;
							});
							SANI_ASSERT(search != std::end(fields));
							// get the parameter type
							Type paramType = search->getType();
							// TODO: transform string to that type
							std::cout << fieldName << " type is " << paramType.getID() << " which is type of " << db.types[paramType.getID()].name << std::endl;
						}
					}
					// TODO type id to another type id conversion
				}
                
				return input;
			}

		}
	}
}

#endif



