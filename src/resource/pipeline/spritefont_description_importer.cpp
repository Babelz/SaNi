#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/platform.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/pipeline/spritefont_description_importer.hpp"
#include "sani/core/parser/xml_parser.hpp"
#include "sani/resource/font_description.hpp"
#include <sstream>
#include "sani/core/parser/xml_util.hpp"
#include <tchar.h>
#include <iostream>
#include <algorithm>




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

			SpriteFontDescriptionImporter::SpriteFontDescriptionImporter() 
				: ContentImporter() {

			}

			SpriteFontDescriptionImporter::~SpriteFontDescriptionImporter() { }

			ResourceItem* SpriteFontDescriptionImporter::import(const String& filename, io::FileSystem* fileSystem) const {
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
				
				XmlNode root, nameNode, sizeNode, spacingNode, regionsNode;
				std::vector<XmlNode> regionNodes;
				CharacterRegionCollection characterRegions;

				doc.firstNode(root);
				root.firstNode("name", nameNode);
				root.firstNode("size", sizeNode);
				root.firstNode("spacing", spacingNode);
				root.firstNode("character_regions", regionsNode);
				
				String nameOfFont(nameNode.value());
				String nameOfFontWithoutExtension(nameOfFont);
				size_t index = 0;
				if ((index = nameOfFontWithoutExtension.rfind(".")) != String::npos) {
					nameOfFontWithoutExtension = nameOfFont.substr(0, index);
				}

				FontDescription* desc = new FontDescription(
					nameOfFontWithoutExtension,
					XmlUtil::get<float>(sizeNode),
					XmlUtil::get<float>(spacingNode)
					);
				
				
				regionsNode.getChildNodes(regionNodes);
				for (auto& regionNode : regionNodes) {
					XmlNode startNode, endNode;
					regionNode.firstNode("start", startNode);
					regionNode.firstNode("end", endNode);

					unsigned short start = XmlUtil::get<uint32>(startNode);
					unsigned short end = XmlUtil::get<uint32>(endNode);
					characterRegions.push_back(std::make_tuple(start, end));
				}
				
				desc->setSetCharacterRegions(characterRegions);

				String basename(filename.substr(0, filename.rfind("\\")));
				String assetFolderPath(basename + "\\" + nameOfFont);
				
				if (fileSystem->fileExists(assetFolderPath)) {
					desc->setFontPath(assetFolderPath);
				}
				else {
					// it is a system font
					if (!platformIsFontInstalled(nameOfFont.c_str())){
						throw std::runtime_error(String("Can find font ") + nameOfFont);
					}
					desc->setFontPath(platformGetFontPath(nameOfFont));
				}
				return desc;
			}
		}
	}
}
#endif