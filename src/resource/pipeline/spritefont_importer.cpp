#include "sani/platform/file/file_system.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/pipeline/spritefont_importer.hpp"
#include "sani/core/parser/xml_parser.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

static FT_Library library;

namespace sani {
	namespace resource {
		namespace pipeline {

			SpriteFontImporter::SpriteFontImporter() 
				: ContentImporter() {
				// this is only called once
				FT_Error error = FT_Init_FreeType(&library);
				if (error) {
					throw std::runtime_error("Failed to initialize freetype");
				}
			}

			SpriteFontImporter::~SpriteFontImporter() { }

			ResourceItem* SpriteFontImporter::import(const String& filename, io::FileSystem* fileSystem) const {
				using namespace sani::io;
				using namespace sani::parser;

				FileStream* stream = nullptr;
				// the file exists so we can just open it
				fileSystem->openFile(filename, Filemode::Read, &stream);
				
				// the file points to XML
				XmlDocument doc;
				try {
					doc.load(stream);
				}
				catch (const XmlException& ex) {
					fileSystem->closeFile(filename);
					throw;
				}
				fileSystem->closeFile(filename);

				XmlNode root, nameNode;
				doc.firstNode(root);
				if (!root.firstNode("name", nameNode)) {
					throw std::runtime_error("SpriteFont missing name node!");
				}
				volatile String nameOfFont(nameNode.value());
				
				
				
				return nullptr;
			}
		}
	}
}