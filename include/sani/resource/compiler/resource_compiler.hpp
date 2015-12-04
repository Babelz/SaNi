#pragma once

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

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
				// TODO move to inl
				template <class T, class U>
				void mapWriter() {
					lookup[std::type_index(typeid(T))] = new U;
				}

				// TODO move to inl
				template <class T, class U>
				void mapProcessor() {
					processors[std::type_index(typeid(T))] = new U;
				}

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

#endif