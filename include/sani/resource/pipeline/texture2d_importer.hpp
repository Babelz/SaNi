#pragma once
#include "sani/resource/pipeline/content_importer.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/forward_declare.hpp"
#include <vector>

SANI_FORWARD_DECLARE_2(sani, io, FileSystem);

namespace sani {
	using namespace io;
	namespace resource {

		struct Texture2DContent;

		namespace pipeline {
			class Texture2DImporterImpl {
			private:
				std::vector<String> supportedFileTypes;
			public:
				Texture2DImporterImpl();
				~Texture2DImporterImpl() = default;
				Texture2DContent* import(const String& filename, FileSystem* fileSystem);
			};
			typedef ContentImporter<Texture2DContent, Texture2DImporterImpl> Texture2DImporter;
		}
	}
}