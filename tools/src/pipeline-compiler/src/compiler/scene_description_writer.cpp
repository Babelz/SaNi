#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/resource/compiler/scene_description_writer.hpp"
#include "sani/resource/compiler/resource_writer.hpp"
#include <sstream>

namespace sani {
	namespace resource {
		namespace compiler {

			void type2type(ResourceWriter* writer, const SceneDescription::PrimitiveField& field);

			SceneDescriptionWriter::SceneDescriptionWriter() {

			}

			SceneDescriptionWriter::~SceneDescriptionWriter() {

			}

			void SceneDescriptionWriter::write(ResourceWriter* writer, const void* value) {
				const SceneDescription* content = static_cast<const SceneDescription*>(value);
				writer->write(content->name);
				writer->write7BitEncodedInt(content->assetFolders.size());
				
				for (uint32 i = 0; i < content->assetFolders.size(); ++i) {
					auto& folder = content->assetFolders[i];
					writer->write(folder.name);
					auto& assets = content->assets.at(folder.id);
					writer->write7BitEncodedInt(assets.size());
					for (auto& asset : assets) {
						writer->write(asset.name);
					}
				}

				// TODO only one for now fix this
				for (auto& componentData : content->components) {
					writer->write7BitEncodedInt(componentData.objectFields.size());
					for (auto& objfield : componentData.objectFields) {
						writer->write(objfield.name);
						writer->write7BitEncodedInt(objfield.fields.size());
						for (auto& field : objfield.fields) {
							writer->write(field.name);
							type2type(writer, field);
						}
					}
				}
			}

			template<typename to, typename from>
			static to lexical_cast(from const &x) {
				std::stringstream os;
				to ret;

				os << x;
				os >> ret;

				return ret;
			}

			void type2type(ResourceWriter* writer, const SceneDescription::PrimitiveField& field) {
				struct ConversionWrapper {
					rtti::TypeID type;
					void(*writeConverison)(ResourceWriter*,const String8&);
				};

#define CONVERT_TO(type) { typeof(type).getID(), [](ResourceWriter* w, const String8& a) { w->write(typeof(type).getID()); w->write(lexical_cast<type>(a)); } }
				static const ConversionWrapper types[] = {
					CONVERT_TO(int32),
					CONVERT_TO(uint32),
					CONVERT_TO(float32),
					CONVERT_TO(float64),
					CONVERT_TO(String8),
					// bool is tricky TODO
				};

				// TODO more types
#undef CONVERT_TO

				auto type = field.type;
				auto search = std::find_if(std::begin(types), std::end(types), [type](const ConversionWrapper& wrapper) {
					return wrapper.type == type;
				});
				
				SANI_ASSERT(search != std::end(types));

				search->writeConverison(writer, field.value);

			}
		}
	}
}

#endif

