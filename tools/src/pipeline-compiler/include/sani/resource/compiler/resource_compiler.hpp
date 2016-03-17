#pragma once

#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include <typeindex>
#include <map>
#include <queue>
#include "sani/resource/compiler/resource_type_writer.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/types.hpp"
#include "sani/resource/pipeline/content_importer.hpp"
#include "sani/resource/processor/resource_processor.hpp"

namespace sani {

	namespace resource {

		namespace compiler {

			class ResourceCompiler {
			private:
				io::FileSystem fileSystem;
				std::map<std::type_index, ResourceTypeWriter*> lookup;
				std::vector<pipeline::ContentImporter*> importers;
				std::map<String, pipeline::ContentImporter*> importerMap;
				std::map<std::type_index, processor::ResourceProcessor*> processors;
				std::queue<String> filesToCompile;
				String contentRoot;
				String filePath;
				String outputPath;

				void initialize();
			public:
				ResourceCompiler();

				~ResourceCompiler();

				template <class T, class U>
				void mapWriter();

				template <class T, class U>
				void mapProcessor();

				ResourceTypeWriter* getWriter(const std::type_index& t) const;

				pipeline::ContentImporter* getImporterFor(const String& asset) const;

				processor::ResourceProcessor* getProcessorFor(const std::type_index& type) const;

				void readBuildFile(const String& root, const String& buildFile);

				void compile(const String& root, const String& path);

				void compileAll(const String& root);

				const String& getFilePath() const;
				const String& getOutputPath() const;
			};
		}
	}
}

#include "sani/resource/compiler/impl/resource_compiler.hpp"

#endif