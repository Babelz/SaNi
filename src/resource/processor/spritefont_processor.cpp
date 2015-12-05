#include "sani/resource/processor/spritefont_processor.hpp"
#include "sani/resource/font_description.hpp"
#include <ft2build.h>
#include <algorithm>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace sani {
	namespace resource {
		namespace processor {

			static FT_Library library;

			SpriteFontProcessor::SpriteFontProcessor() {

			}

			SpriteFontProcessor::~SpriteFontProcessor() {

			}

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

			static FT_Face createFontFace(FontDescription* desc) {
				FT_Face face = nullptr;

				FT_Error error = FT_New_Face(library, desc->getFontPath().c_str(), 0, &face);

				if (error == FT_Err_Unknown_File_Format) {
					throw std::runtime_error("Invalid font file format!");
				}
				else if (error) {
					throw std::runtime_error("Font file could not be read");
				}
				const uint32 size = static_cast<uint32>(desc->getSize());
				const uint32 dpi = 96;
				FT_Set_Char_Size(face, 0, size << 6, dpi, dpi);
				return face;
			}

			ResourceItem* SpriteFontProcessor::process(ResourceItem* input) {
				if (FT_Init_FreeType(&library)) {
					throw std::runtime_error("Failed to initialize freetype");
				}
				FontDescription* desc = static_cast<FontDescription*>(input);
				// import the actual font now
				FT_Face face = createFontFace(desc);
				

				const std::vector<unsigned short>& characters = desc->getCharacters();
				std::vector<Glyph*> glyphs;
				glyphs.reserve(characters.size());

				for (auto character : characters) {
					Glyph* glyph = importGlyph(character, face);
					glyphs.push_back(glyph);
				}

				// font height
				uint32 lineSpacing = face->size->metrics.height >> 6;
				// The height used to calculate the Y offset for each character.
				uint32 yOffsetMin = -face->size->metrics.ascender >> 6;

				std::sort(glyphs.begin(), glyphs.end(), [](Glyph*a, Glyph* b) {
					return a->character < b->character;
				});

				FT_Done_Face(face);
				FT_Done_FreeType(library);
				return nullptr;
			}
		}
	}
}