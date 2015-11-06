#include "sani/resource/compiler/resource_compiler.hpp"
#include "sani/resource/compiler/compilers.hpp"
#include <algorithm>
#include "sani/resource/pipeline/content_importer.hpp"
#include "sani/resource/pipeline/texture2d_importer.hpp"
#include "sani/resource/processor/resource_processor.hpp"
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
				map<Texture2DContent, Texture2DWriter>();
				//map<Effect, EffectWriter>();
				// THIS IS FOR DEBUG
				importers["tuksu.png"] = new pipeline::Texture2DImporter;
			}

			void ResourceCompiler::compile(const String& root, const String& path) {
				using namespace sani::resource::pipeline;
				using namespace sani::resource::processor;

				const static String outExtension(".out");

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

				ResourceProcessor* processor ;
				//void* binary = processor->process(data);
				std::cout << typeid(*data).name() << std::endl;
				//std::cout << typeid(*binary).name() << std::endl;

				//ResourceWriter writer(file, this);
			//	writer.flush(binary);
				
			}

			pipeline::ContentImporter* ResourceCompiler::getImporterFor(const String& asset) const {
				if (!importers.count(asset)) {
					throw std::runtime_error("No importer specified for " + asset);
				}
				return importers.at(asset);
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