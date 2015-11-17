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

				String vertexPath(filename + ".vertex");
				String fragmentPath(filename + ".fragment");

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
				content->setVertexCode(fragmentSource);

				fileSystem->closeFile(filename+".vertex");
				fileSystem->closeFile(filename+".fragment");

				return content;
			}
		}
	}
}