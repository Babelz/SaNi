#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/resource/pipeline/effect_importer.hpp"
#include "sani/resource/effect_content.hpp"
namespace sani {
	namespace resource {
		namespace pipeline {
			EffectImporter::EffectImporter() {}
			EffectImporter::~EffectImporter(){}

			ResourceItem* EffectImporter::import(const String& filename, io::FileSystem* fileSystem) const {
				io::FileStream* vertex = nullptr;
				io::FileStream* fragment = nullptr;

				String file(filename);
				// get rid of extension
				size_t index = 0;
				if ((index = filename.rfind('.')) != String::npos) {
					file = file.substr(0, index);
				}

				String vertexPath(file + ".vert");
				String fragmentPath(file + ".frag");

				if (!fileSystem->openFile(vertexPath, io::Filemode::Read, &vertex)) {
					throw std::runtime_error("cant open vertex shader file");
				}
				if (!fileSystem->openFile(fragmentPath, io::Filemode::Read, &fragment)) {
					throw std::runtime_error("cant open fragment shader file");
				}

				String vertexSource(fileSystem->getFileDataString(vertexPath));
				String fragmentSource(fileSystem->getFileDataString(fragmentPath));

				EffectContent* content = new EffectContent;
				content->setVertexCode(vertexSource);
				content->setFragmentCode(fragmentSource);

				fileSystem->closeFile(vertexPath);
				fileSystem->closeFile(fragmentPath);

				return content;
			}
		}
	}
}
#endif