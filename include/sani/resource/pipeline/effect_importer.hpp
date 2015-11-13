#pragma once

#include "sani/resource/pipeline/content_importer.hpp"

namespace sani {
	namespace resource {
		namespace pipeline {
			class EffectImporter : public ContentImporter {
			private:
				std::vector<String> supportedFileTypes;
			public:
				EffectImporter();
				~EffectImporter();
				ResourceItem* import(const String& filename, io::FileSystem* fileSystem) const;
			};
		}
	}
}