#pragma once

#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "sani/resource/pipeline/content_importer.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/texture2d_content.hpp"
#include "sani/forward_declare.hpp"
#include <vector>

SANI_FORWARD_DECLARE_2(sani, io, FileSystem);
SANI_FORWARD_DECLARE_2(sani, resource, ResourceItem);

namespace sani {

	using namespace io;

	namespace resource {

		namespace pipeline {

			class Texture2DImporter : public ContentImporter {
			private:
				std::vector<String> supportedFileTypes;
			public:
				Texture2DImporter();
				~Texture2DImporter();

				ResourceItem* import(const String& filename, FileSystem* fileSystem) const override;

				virtual String getImporterName() const {
					return "sani::resource::pipeline::Texture2DImporter";
				}
			};
		}
	}
}
#endif