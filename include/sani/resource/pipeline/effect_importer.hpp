#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/pipeline/content_importer.hpp"

namespace sani {
	namespace resource {
		namespace pipeline {
			class EffectImporter : public ContentImporter {
			public:
				EffectImporter();
				~EffectImporter();
				ResourceItem* import(const String& filename, io::FileSystem* fileSystem) const;
				virtual String getImporterName() const {
					return "sani::resource::pipeline::EffectImporter";
				}
			};
		}
	}
}
#endif