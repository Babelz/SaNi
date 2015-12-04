#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/platform/file/file_system.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/pipeline/spritefont_importer.hpp"
#include "sani/core/parser/xml_parser.hpp"
#include <tchar.h>
#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H

static FT_Library library;

int CALLBACK EnumFontFamiliesExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, int FontType, LPARAM lParam) {
	LPARAM* l = (LPARAM*)lParam;
	*l = TRUE;
	return 0;
}

static bool platformIsFontInstalled(const char* faceName) {
	const int MaxSize = 512;
	if (strlen(faceName) > MaxSize) {
		throw std::runtime_error("Not enough memory");
	}
	wchar_t lz[MaxSize] = { 0 };
	mbstowcs(lz, faceName, strlen(faceName));
	HDC hdc = GetDC(NULL);
	LOGFONT lf = { 0 };
	lf.lfCharSet = DEFAULT_CHARSET;
	_tcscpy(lf.lfFaceName, lz);
	LPARAM lparam = 0;
	EnumFontFamiliesEx(hdc, &lf, (FONTENUMPROC)EnumFontFamiliesExProc, (LPARAM)&lparam, 0);
	return lparam ? true : false;
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
					(void)ex;
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
					if (platformIsFontInstalled(nameOfFont.c_str())) {
						std::cout << "jeee" << std::endl;
					}
				}
				
				
				return nullptr;
			}
		}
	}
}
#endif