#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/platform/file/file_system.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/pipeline/spritefont_importer.hpp"
#include "sani/core/parser/xml_parser.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

static FT_Library library;

int CALLBACK EnumFontFamiliesExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, int FontType, LPARAM lParam);
static void getInstalledPlatformFonts() {
	HDC hdc = GetDC(NULL);
	LOGFONT lf = { 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
		0, L"Arial" };
	EnumFontFamiliesEx(hdc, &lf, (FONTENUMPROC)EnumFontFamiliesExProc, 0, 0);
}

int CALLBACK EnumFontFamiliesExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, int FontType, LPARAM lParam) {
	printf("%s\n", lpelfe->elfFullName);
	return 1;
}

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
				String nameOfFont(nameNode.value());
				

				// TODO context maybe?
				String basename(filename.substr(0, filename.rfind("\\")));
				// it is a system font probably
				if (!fileSystem->fileExists(basename + "\\" + nameOfFont)) {
					getInstalledPlatformFonts();
				}
				
				
				return nullptr;
			}
		}
	}
}
#endif