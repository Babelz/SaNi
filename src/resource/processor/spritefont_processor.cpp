#include "sani/resource/processor/spritefont_processor.hpp"
#include "sani/resource/font_description.hpp"
#include <ft2build.h>
#include <algorithm>
#include "sani/resource/spritefont_content.hpp"
#include "sani/core/math/rectangle.hpp"
#include FT_FREETYPE_H
#include FT_STROKER_H
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

			struct Span {
				Span() { }
				Span(int _x, int _y, int _width, int _coverage)
					: x(_x), y(_y), width(_width), coverage(_coverage) { }

				int x, y, width, coverage;
			};

			static void rasterSpan(const int y, const int count, const FT_Span * const spans, void * const user) {
				std::vector<Span>* sptr = (std::vector<Span> *)user;
				for (int i = 0; i < count; ++i) {
					sptr->push_back(Span(spans[i].x, y, spans[i].len, spans[i].coverage));
				}
			}

			static void renderSpans(FT_Outline* outline, std::vector<Span>* spans) {
				FT_Raster_Params params;
				memset(&params, 0, sizeof(params));
				params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
				params.gray_spans = rasterSpan;
				params.user = spans;

				FT_Outline_Render(library, outline, &params);
			}

			static Glyph* importGlyph(FontDescription* desc, unsigned long character, FT_Face face) {
				Glyph* g = nullptr;
				
				FT_UInt gindex = FT_Get_Char_Index(face, character);
				
				if (FT_Load_Glyph(face, gindex, FT_LOAD_NO_BITMAP)) {
					throw std::runtime_error("FT_Load_Glyph failed");
				}
				
				if (desc->getOutlineType() == OutlineType::Outer) {
					if (face->glyph->format != FT_GLYPH_FORMAT_OUTLINE) {
						throw std::runtime_error("No outline");
					}

					int32 outlineWidth = static_cast<int32>(desc->getOutlineWidth()* 64.f);
					FT_Stroker stroker;
					FT_Glyph glyph;
					FT_Outline* outline = nullptr;
					std::vector<Span> spans, outlineSpans;

					renderSpans(&face->glyph->outline, &spans);

					// setup stroker
					FT_Stroker_New(library, &stroker);

					FT_Stroker_Set(stroker,
						outlineWidth,
						FT_STROKER_LINECAP_ROUND,
						FT_STROKER_LINEJOIN_ROUND,
						0);

					if (FT_Get_Glyph(face->glyph, &glyph)){
						throw std::runtime_error("Cant get glyph");
					}

					FT_Glyph_StrokeBorder(&glyph, stroker, 0, 1);
					if (glyph->format != FT_GLYPH_FORMAT_OUTLINE) {
						throw std::runtime_error("Not outline");
					}

					// render the outline spans to the span list
					outline = &reinterpret_cast<FT_OutlineGlyph>(glyph)->outline;

					

					// Clean up afterwards.
					FT_Stroker_Done(stroker);
					FT_Done_Glyph(glyph);

					// TODO what now
					if (spans.empty()) {
						throw std::logic_error("wat");
					}

					// build
					sani::math::Recti rect(
						spans.front().x,
						spans.front().y,
						1, 1
						);

					for (auto& s : spans) {
						rect.include(sani::math::Vec2i(s.x, s.y));
						rect.include(sani::math::Vec2i(s.x + s.width - 1, s.y));
					}

					for (auto& s : outlineSpans) {
						rect.include(sani::math::Vec2i(s.x, s.y));
						rect.include(sani::math::Vec2i(s.x + s.width - 1, s.y));
					}

					float32 bearingX = static_cast<float32>(face->glyph->metrics.horiBearingX >> 6); // left
					float32 bearingY = static_cast<float32>(face->glyph->metrics.horiBearingY >> 6); // top
					float32 advance = static_cast<float32>(face->glyph->advance.x >> 6); // offset

					// Get some metrics of our image.
					uint32 imgWidth = rect.w,
						imgHeight = rect.h,
						imgSize = imgWidth * imgHeight;
				}

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
					Glyph* glyph = importGlyph(desc, character, face);
					glyphs.push_back(glyph);
				}

				// font height
				float lineSpacing = static_cast<float>(face->size->metrics.height >> 6);
				// The height used to calculate the Y offset for each character.
				float yOffsetMin = static_cast<float>(-face->size->metrics.ascender >> 6);

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