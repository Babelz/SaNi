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
#include <ft2build.h>
#include <iostream>
#include <algorithm>
#include FT_FREETYPE_H
#include FT_GLYPH_H

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

			SpriteFontDescriptionImporter::SpriteFontDescriptionImporter() 
				: ContentImporter() {
				// this is only called once
				FT_Error error = FT_Init_FreeType(&library);
				if (error) {
					throw std::runtime_error("Failed to initialize freetype");
				}
			}

			SpriteFontDescriptionImporter::~SpriteFontDescriptionImporter() { }

			class Glyph {
			public:
				unsigned long character;
				unsigned char* pixels;
				uint32 dataLength;
				uint32 width;
				uint32 height;
				float a;
				float b;
				float c;
				float xOffset;
				float yOffset;
				float xAdvance;
			public:
				Glyph(unsigned long character, unsigned char* pixels, uint32 dataLength, uint32 width, uint32 height)
					: character(character), pixels(pixels), dataLength(dataLength), 
					width(width), height(height), a(0), b(0), c(0), xOffset(0), yOffset(0), xAdvance(0) {

				}
			};

			static Glyph* importGlyph(unsigned long character, FT_Face face) {
				Glyph* g = nullptr;
				if (FT_Load_Char(face, character, FT_LOAD_RENDER)) {
					throw std::runtime_error("aaa");
				}

				// if the font has the char
				if (face->glyph->bitmap.width > 0 && face->glyph->bitmap.rows > 0) {
					uint32 width = face->glyph->bitmap.width;
					uint32 rows = face->glyph->bitmap.rows;
					// TODO DEBUG
					/*unsigned char** pixels = new unsigned char*[rows];
					for (size_t i = 0; i < rows; ++i) {
						pixels[i] = new unsigned char[width];
					}*/
					unsigned char* alphas = new unsigned char[width * rows];
					std::memcpy(alphas, face->glyph->bitmap.buffer, width * rows);
					g = new Glyph(character, alphas, width*rows, width, rows);
				}
				// if the font doesnt have the char
				else {
					int gHA = face->glyph->metrics.horiAdvance >> 6;
					int gVA = face->size->metrics.height >> 6;

					gHA = gHA > 0 ? gHA : gVA;
					gVA = gVA > 0 ? gVA : gHA;
					g = new Glyph(character, new unsigned char[gHA * gVA], gHA*gVA, gHA, gVA);
				}
				float a = static_cast<float>(face->glyph->metrics.horiBearingX >> 6);
				float b = static_cast<float>(face->glyph->metrics.width >> 6);
				float c = static_cast<float>((face->glyph->metrics.horiAdvance >> 6) - (a + b));
				
				g->xOffset = static_cast<float>(-(face->glyph->advance.x >> 6));
				g->xAdvance = static_cast<float>(face->glyph->metrics.horiAdvance >> 6);
				g->yOffset = static_cast<float>(-(face->glyph->metrics.horiBearingY >> 6));
				g->a = a; g->b = b; g->c = c;
				return g;
			}

			static FT_Face createFontFace(parser::XmlDocument& doc, const String& basename, io::FileSystem* fs) {
				using namespace sani::parser;
				FT_Face face = nullptr;
				XmlNode root, nameNode, sizeNode;

				doc.firstNode(root);
				if (!root.firstNode("name", nameNode)) {
					throw std::runtime_error("SpriteFont missing name node!");
				}

				if (!root.firstNode("size", sizeNode)) {
					throw std::runtime_error("SpriteFont missing size node!");
				}
				String nameOfFont(nameNode.value());

				// it is a system font probably
				if (!fs->fileExists(basename + "\\" + nameOfFont)) {
					if (platformIsFontInstalled(nameOfFont.c_str())) {
						String fontFilePath(platformGetFontPath(nameOfFont));
						FT_Error error = FT_New_Face(library, fontFilePath.c_str(), 0, &face);

						if (error == FT_Err_Unknown_File_Format) {
							throw std::runtime_error("Invalid font file format!");
						}
						else if (error) {
							throw std::runtime_error("Font file could not be read");
						}
					}
				}
				else {
					throw std::logic_error("not impl");
				}
				uint32 size = XmlUtil::get<uint32>(sizeNode);
				const uint32 dpi = 96;
				FT_Set_Char_Size(face, 0, size * 64, dpi, dpi);
				return face;
			}

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
				

				FontDescription* desc = new FontDescription(
					nameNode.value(),
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
				return desc;
				/*

				// TODO context maybe?
				String basename(filename.substr(0, filename.rfind("\\")));

				FT_Face face = createFontFace(doc, basename, fileSystem);

				
				
				std::vector<Glyph*> glyphs;
				for (auto& regionNode : regionNodes) {
					uint32 width, height;
					width = height = 0u;
					for (unsigned long character = start; character <= end; ++character) {
						Glyph* glyph = importGlyph(character, face);
						glyphs.push_back(glyph);
					}
				}

				// font height
				uint32 lineSpacing = face->size->metrics.height >> 6;
				// The height used to calculate the Y offset for each character.
				uint32 yOffsetMin = -face->size->metrics.ascender >> 6;

				std::sort(glyphs.begin(), glyphs.end(), [](Glyph*a, Glyph* b) {
					return a->character < b->character;
				});
			
				*/
			}
		}
	}
}
#endif