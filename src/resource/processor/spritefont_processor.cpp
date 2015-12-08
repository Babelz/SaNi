#include "sani/resource/processor/spritefont_processor.hpp"
#include "sani/resource/font_description.hpp"
#include <ft2build.h>
#include <algorithm>
#include "sani/resource/spritefont_content.hpp"
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

			struct GlyphWrapper {
				Glyph* source;
				uint32 x;
				uint32 y;
				uint32 width;
				uint32 height;
			};

			static int makeValidTextureSize(uint32 value, bool powerOfTwo) {
				const uint32 blockSize = 4u;
				if (powerOfTwo) {
					uint32 pwr = blockSize;
					while (pwr < value) pwr <<= 1;
					return pwr;
				}
				return (value + blockSize - 1) & ~(blockSize - 1);
			}

			static uint32 guessOutputWidth(const std::vector<Glyph*>& sourceGlyphs) {
				uint32 maxWidth = 0;
				uint32 totalSize = 0;
				for (auto* g : sourceGlyphs) {
					maxWidth = std::max(maxWidth, g->width);
					totalSize += g->width * g->height;
				}
				uint32 width = std::max((uint32)std::sqrt(totalSize), maxWidth);
				return makeValidTextureSize(width, true);
			}

			static int findIntersectingGlpyh(const std::vector<GlyphWrapper>& glyphs, uint32 index, uint32 x, uint32 y) {
				uint32 w = glyphs[index].width;
				uint32 h = glyphs[index].width;

				for (uint32 i = 0; i < index; ++i) {
					if (glyphs[i].x >= x + w) continue;
					if (glyphs[i].x + glyphs[i].width <= x) continue;
					if (glyphs[i].y >= y + h) continue;
					if (glyphs[i].y + glyphs[i].height <= y) continue;
					return i;
				}
				return -1;
			}

			static void positionGlyph(std::vector<GlyphWrapper>& glyphs, uint32 index, uint32 outputWidth) {
				uint32 x = 0;
				uint32 y = 0;

				while (true) {
					int intersects = findIntersectingGlpyh(glyphs, index, x, y);
					if (intersects < 0) {
						glyphs[index].x = x;
						glyphs[index].y = y;
						return;
					}
					// Skip past the existing glyph that we collided with.
					x = glyphs[intersects].x + glyphs[intersects].width;
					// If we ran out of room to move to the right, try the next line down instead.
					if (x + glyphs[index].width > outputWidth) {
						x = 0;
						y++;
					}
				}
			}
			struct Color {
				float r;
				float g;
				float b;
				float a;
			};
			static void copyGlyphsToOutput(std::vector<GlyphWrapper>& glyphs, uint32 width, uint32 height) {
				Color** pixels = new Color*[height];
				for (size_t i = 0; i < height; ++i) {
					pixels[i] = new Color[width];
				}

				for (auto& glyph : glyphs) {

				}
			}

			static void arrangeGlyphs(const std::vector<Glyph*>& sourceGlyphs) {
				std::vector<GlyphWrapper> glyphs;
				glyphs.reserve(sourceGlyphs.size());
				for (size_t i = 0; i < sourceGlyphs.size(); ++i) {
					Glyph* glyph = sourceGlyphs[i];
					glyphs.push_back(GlyphWrapper{
						glyph,
						0,
						0,
						glyph->width + 2u,
						glyph->height + 2u
					});
				}

				std::sort(glyphs.begin(), glyphs.end(), [](GlyphWrapper& a, GlyphWrapper& b) {
					const uint32 heightWeight = 1024u;
					uint32 aSize = a.height * heightWeight + a.width;
					uint32 bSize = b.height * heightWeight + b.width;
					if (aSize != bSize)
						return bSize < aSize;

					return a.source->character < b.source->character;
				});

				uint32 outputWidth = guessOutputWidth(sourceGlyphs);
				uint32 outputHeight = 0;

				for (size_t i = 0; i < glyphs.size(); ++i) {
					positionGlyph(glyphs, i, outputWidth);
					outputHeight = std::max(outputHeight, glyphs[i].y + glyphs[i].height);
				}

				outputHeight = makeValidTextureSize(outputHeight, true);


			}

			ResourceItem* SpriteFontProcessor::process(ResourceItem* input) {
				if (FT_Init_FreeType(&library)) {
					throw std::runtime_error("Failed to initialize freetype");
				}

				FontDescription* desc = static_cast<FontDescription*>(input);
				SpriteFontContent* output = new SpriteFontContent(desc);
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
				float lineSpacing = static_cast<float>(face->size->metrics.height >> 6);
				// The height used to calculate the Y offset for each character.
				float yOffsetMin = static_cast<float>(-face->size->metrics.ascender >> 6);

				std::sort(glyphs.begin(), glyphs.end(), [](Glyph*a, Glyph* b) {
					return a->character < b->character;
				});

				arrangeGlyphs(glyphs);

				FT_Done_Face(face);
				FT_Done_FreeType(library);

				return nullptr;
			}
		}
	}
}