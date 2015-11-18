#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/compiler/resource_compiler.hpp"
#include "sani/resource/compiler/compilers.hpp"
#include <algorithm>
#include "sani/resource/pipeline/importers.hpp"
#include "sani/resource/processor/processors.hpp"
#include "sani/resource/effect_content.hpp"
#include <iostream>
namespace sani {
	namespace resource {
		namespace compiler {
			ResourceCompiler::ResourceCompiler() {
				initialize();
			}

			ResourceCompiler::~ResourceCompiler() {
				for (auto& kv : lookup) {
					delete kv.second;
				}
			}

			void ResourceCompiler::initialize() {
				using namespace sani::resource::compiler;
				mapWriter<Texture2DContent, Texture2DWriter>();
				mapWriter<EffectContent, EffectWriter>();
				//map<Effect, EffectWriter>();
				// THIS IS FOR DEBUG
				importers["tuksu.png"] = new pipeline::Texture2DImporter;
				importers["polygon.vert"] = new pipeline::EffectImporter;
				importers["texture.vert"] = new pipeline::EffectImporter;
				mapProcessor<Texture2DContent, processor::Texture2DProcessor>();
				mapProcessor<EffectContent, processor::EffectProcessor>();
			}

			void ResourceCompiler::compile(const String& root, const String& path) {
				using namespace sani::resource::pipeline;
				using namespace sani::resource::processor;

				const static String outExtension(".snb");

				if (!fileSystem.fileExists(root + path)) {
					throw "file not found";
				}

				String filename(path);
				size_t index = 0;
				if ((index = path.rfind(".")) != String::npos) {
					filename = (path.substr(0, index));
				}
				
				filePath = root + path;
				outputPath = String(root + filename + outExtension);
				io::FileStream* file;
				if (!fileSystem.openFile(outputPath, io::Filemode::Truncate, &file)) {
					throw "cant open file!";
				}
				ContentImporter* importer = getImporterFor(path);
				ResourceItem* data = importer->import(filePath, &fileSystem);

				ResourceProcessor* processor = getProcessorFor(std::type_index(typeid(*data)));
				ResourceItem* binary = processor->process(data);
				
				std::cout << typeid(*binary).name() << std::endl;

				ResourceWriter writer(file, this);
				writer.flush(std::type_index(typeid(*binary)), binary);
				
			}

			processor::ResourceProcessor* ResourceCompiler::getProcessorFor(const std::type_index& type) const {
				if (!processors.count(type)) {
					throw std::runtime_error(String("No processor for ") + type.name());
				}
				return processors.at(type);
			}

			pipeline::ContentImporter* ResourceCompiler::getImporterFor(const String& asset) const {
				if (!importers.count(asset)) {
					throw std::runtime_error("No importer specified for " + asset);
				}
				return importers.at(asset);
			}


			ResourceTypeWriter* ResourceCompiler::getWriter(const std::type_index& t) const {
				return lookup.at(t);
			}


			const String& ResourceCompiler::getFilePath() const {
				return filePath;
			}
			const String& ResourceCompiler::getOutputPath() const {
				return outputPath;
			}
		}
	}
}

#endif