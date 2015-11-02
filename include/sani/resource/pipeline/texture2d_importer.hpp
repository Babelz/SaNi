#pragma once
#include "sani/resource/pipeline/content_importer.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/texture2d_content.hpp"
#include "sani/forward_declare.hpp"
#include <vector>

SANI_FORWARD_DECLARE_2(sani, io, FileSystem);

namespace sani {
	using namespace io;
	namespace resource {

		namespace pipeline {
			class Texture2DImporterImpl {
			private:
				std::vector<String> supportedFileTypes;
			public:
				Texture2DImporterImpl() {
					supportedFileTypes.push_back(".png");
				}
				~Texture2DImporterImpl() { }
				Texture2DContent* import(const String& filename, FileSystem* fileSystem) const;
			};
			typedef ContentImporter<Texture2DContent, Texture2DImporterImpl> Texture2DImporter;
		}
	}
}