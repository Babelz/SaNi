#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/platform/file/file_system.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/pipeline/spritefont_importer.hpp"
#include "sani/core/parser/xml_parser.hpp"
#include <sstream>
#include "sani/core/parser/xml_util.hpp"
#include <tchar.h>
#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H

static FT_Library library;

static int CALLBACK EnumFontFamiliesExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, int FontType, LPARAM lParam) {
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

// credits http://stackoverflow.com/questions/11387564/get-a-font-filepath-from-name-and-style-in-c-windows

static String platformGetFontPath(const String& faceName) {
	static const LPWSTR fontRegistryPath = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
	HKEY hKey;
	LONG result;
	std::wstring wsFaceName(faceName.begin(), faceName.end());

	// Open Windows font registry key
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKey);
	if (result != ERROR_SUCCESS) {
		throw std::runtime_error("Cant open registry!");
	}

	DWORD maxValueNameSize, maxValueDataSize;
	result = RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);

	if (result != ERROR_SUCCESS) {
		throw std::runtime_error("Cant query registry!");
	}

	DWORD valueIndex = 0;
	LPWSTR valueName = new WCHAR[maxValueNameSize];
	LPBYTE valueData = new BYTE[maxValueDataSize];
	DWORD valueNameSize, valueDataSize, valueType;
	std::wstring wsFontFile;

	// Look for a matching font name
	do {

		wsFontFile.clear();
		valueDataSize = maxValueDataSize;
		valueNameSize = maxValueNameSize;

		result = RegEnumValue(hKey, valueIndex, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);

		valueIndex++;

		if (result != ERROR_SUCCESS || valueType != REG_SZ) {
			continue;
		}

		std::wstring wsValueName(valueName, valueNameSize);

		// Found a match
		if (_wcsnicmp(wsFaceName.c_str(), wsValueName.c_str(), wsFaceName.size()) == 0) {
			wsFontFile.assign((LPWSTR)valueData, valueDataSize);
			break;
		}
	} while (result != ERROR_NO_MORE_ITEMS);

	delete[] valueName;
	delete[] valueData;

	RegCloseKey(hKey);

	if (wsFontFile.empty()) {
		throw std::runtime_error("Did not find matching font!");
	}

	// Build full font file path
	WCHAR winDir[MAX_PATH];
	GetWindowsDirectory(winDir, MAX_PATH);

	std::wstringstream ss;
	ss << winDir << "\\Fonts\\" << wsFontFile;
	wsFontFile = ss.str();

	return String(wsFontFile.begin(), wsFontFile.end());
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

				XmlNode root, nameNode, sizeNode;
				doc.firstNode(root);
				if (!root.firstNode("name", nameNode)) {
					throw std::runtime_error("SpriteFont missing name node!");
				}

				if (!root.firstNode("size", sizeNode)) {
					throw std::runtime_error("SpriteFont missing size node!");
				}

				String nameOfFont(nameNode.value());
				

				// TODO context maybe?
				String basename(filename.substr(0, filename.rfind("\\")));

				FT_Face face;
				
				// it is a system font probably
				if (!fileSystem->fileExists(basename + "\\" + nameOfFont)) {
					if (platformIsFontInstalled(nameOfFont.c_str())) {
						String fontFilePath(platformGetFontPath(nameOfFont));
						FT_Error error = FT_New_Face(library, fontFilePath.c_str(), 0, &face);

						if (error == FT_Err_Unknown_File_Format) {
							throw std::runtime_error("Invalid font file format!");
						}
						else if (error) {
							throw std::runtime_error("Font file could not be read");
						}
						uint32 size = XmlUtil::get<uint32>(sizeNode);
						error = FT_Set_Char_Size(
							face,
							0, // same as height
							size * 64u,
							300,
							300);

					}
				}
				
				
				return nullptr;
			}
		}
	}
}
#endif