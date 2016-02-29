#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/compiler/resource_compiler.hpp"
#include "sani/resource/compiler/compilers.hpp"
#include <algorithm>
#include "sani/resource/pipeline/importers.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/processor/processors.hpp"
#include "sani/resource/effect_content.hpp"
#include "sani/resource/compiler/bitmap_content_writer.hpp"
#include "sani/core/parser/xml_parser.hpp"
#include <iostream>
#include "sani/resource/font_description.hpp"
#include "sani/resource/pipeline/scene_description_importer.hpp"
#include "sani/resource/scene.hpp"
#include "sani/resource/processor/scene_description_processor.hpp"
#include "sani/resource/compiler/scene_description_writer.hpp"

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
				mapWriter<SpriteFontContent, SpriteFontWriter>();
				mapWriter<BitmapContent, BitmapContentWriter>();
				mapWriter<SceneDescription, SceneDescriptionWriter>();
				//map<Effect, EffectWriter>();
				importers.reserve(32u);
				importers.push_back(new pipeline::Texture2DImporter);
				importers.push_back(new pipeline::EffectImporter);
				importers.push_back(new pipeline::SpriteFontDescriptionImporter);
				importers.push_back(new pipeline::SceneDescriptionImporter);

				mapProcessor<Texture2DContent, processor::Texture2DProcessor>();
				mapProcessor<EffectContent, processor::EffectProcessor>();
				mapProcessor<FontDescription, processor::SpriteFontProcessor>();
				mapProcessor<SceneDescription, processor::SceneDescriptionProcessor>();
			}

			void ResourceCompiler::readBuildFile(const String& root, const String& buildFile) {
				using namespace parser;
				const String fullPath(root + buildFile);

				FileStream* stream;
				if (!fileSystem.openFile(fullPath, Filemode::Read, &stream)) {
					throw std::runtime_error("cant open build file");
				}

				parser::XmlDocument document;

				try {
					document.load(stream);
					XmlNode assets;
					
					if (!document.firstNode("assets", assets)) return;

					std::vector<XmlNode> childs;
					assets.getChildNodes(childs);

					for (auto& child : childs) {
						XmlAttribute filenameAttr;
						if (!child.attribute("filename", filenameAttr)) {
							throw std::runtime_error("No filename attribute");
						}

						XmlAttribute importerAttr;
						if (!child.attribute("importer", importerAttr)) {
							throw std::runtime_error("No importer attribute");
						}

						String importerString = importerAttr.value();
						auto it = std::find_if(importers.begin(), importers.end(), [&importerString](pipeline::ContentImporter* imp) {
							return imp->getImporterName() == importerString;
						});

						if (it == importers.end()) {
							throw std::runtime_error(String("No importer called ") + importerString);
						}

						// TODO do we need processor and shit?
						pipeline::ContentImporter* importer = *it;
						importerMap[filenameAttr.value()] = importer;

						filesToCompile.push(filenameAttr.value());
					}
				}
				catch (const parser::XmlException& ex) {
					std::cout << ex.what() << std::endl;
				}

				fileSystem.closeFile(fullPath);
			}

			void ResourceCompiler::compileAll(const String& root) {
				while (!filesToCompile.empty()) {
					compile(root, filesToCompile.front());
					filesToCompile.pop();
				}
			}

			void ResourceCompiler::compile(const String& root, const String& path) {
				using namespace sani::resource::pipeline;
				using namespace sani::resource::processor;

				const static String outExtension(".snb");
				std::cout << "Compiling " << path << " ";
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

				ResourceWriter writer(file, this);
				writer.flush(std::type_index(typeid(*binary)), binary);
				
				std::cout << "-> " << filename << outExtension << std::endl;
			}

			processor::ResourceProcessor* ResourceCompiler::getProcessorFor(const std::type_index& type) const {
				if (!processors.count(type)) {
					throw std::runtime_error(String("No processor for ") + type.name());
				}

				return processors.at(type);
			}

			pipeline::ContentImporter* ResourceCompiler::getImporterFor(const String& asset) const {
				if (!importerMap.count(asset)) {
					throw std::runtime_error("No importer specified for " + asset);
				}

				return importerMap.at(asset);
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