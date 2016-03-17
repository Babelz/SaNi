#pragma once

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "sani/resource/pipeline/content_importer.hpp"
#include <vector>
#include <unordered_map>


namespace sani {
	namespace resource {
		namespace pipeline {
			class SceneDescriptionImporter : public ContentImporter {
			public:
				SceneDescriptionImporter();
				~SceneDescriptionImporter();

				ResourceItem* import(const String& filename, io::FileSystem* fileSystem) const;

				virtual String getImporterName() const {
					return "sani::resource::pipeline::SceneDescriptionImporter";
				}
			};
		}
	}
}

#endif