#include "sani/resource/compiler/resource_compiler.hpp"
#include "sani/resource/compiler/compilers.hpp"
#include <algorithm>

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
			}

			void ResourceCompiler::compile(const String& path) {
				const static String outExtension(".out");

				if (!fileSystem.fileExists(path)) {
					throw "file not found";
				}

				String filename(path);
				size_t index = 0;
				if ((index = path.rfind(".")) != String::npos) {
					filename = (path.substr(0, index));
				}
				
				filePath = path;
				outputPath = String(filename + outExtension);
				io::FileStream* file;
				if (!fileSystem.openFile(outputPath, io::Filemode::Truncate, &file)) {
					throw "cant open file!";
				}

				ResourceWriter writer(file);
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