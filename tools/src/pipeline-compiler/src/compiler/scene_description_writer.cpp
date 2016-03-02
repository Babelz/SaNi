#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/resource/compiler/scene_description_writer.hpp"
#include "sani/resource/compiler/resource_writer.hpp"

namespace sani {
	namespace resource {
		namespace compiler {

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
				
			}

		}
	}
}

#endif

