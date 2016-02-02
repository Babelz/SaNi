#include "sani/resource/processor/spritefont_processor.hpp"
#include "sani/resource/font_description.hpp"
#include <ft2build.h>
#include <algorithm>
#include <numeric>
#include "sani/resource/spritefont_content.hpp"
#include "sani/core/math/rectangle.hpp"
#include "sani/resource/bitmap_content.hpp"
#include "sani/core/math/vector4.hpp"

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
				BitmapContent* pixels;
				unsigned long character;
				float32 bearingX;
				float32 bearingY;
				float32 advance;
				sani::math::Rect32i source;
			public:
				Glyph() : pixels(nullptr), character('\0') {}
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

			struct Rect {
				Rect() { }
				Rect(float left, float top, float right, float bottom)
					: xmin(left), xmax(right), ymin(top), ymax(bottom) { }

				void include(const sani::math::Vec2f &r) {
					xmin = std::min(xmin, r.x);
					ymin = std::min(ymin, r.y);
					xmax = std::max(xmax, r.x);
					ymax = std::max(ymax, r.y);
				}

				float width() const { return xmax - xmin + 1; }
				float height() const { return ymax - ymin + 1; }

				float xmin, xmax, ymin, ymax;
			};

			static void importGlyph(FontDescription* desc, unsigned long character, FT_Face face, Glyph& out) {
				
				out.character = character;
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
					renderSpans(outline, &outlineSpans);

					// Clean up afterwards.
					FT_Stroker_Done(stroker);
					FT_Done_Glyph(glyph);


					float32 bearingX = static_cast<float32>(face->glyph->metrics.horiBearingX >> 6); // left
					float32 bearingY = static_cast<float32>(face->glyph->metrics.horiBearingY >> 6); // top
					float32 advance = static_cast<float32>(face->glyph->advance.x >> 6); // offset

					out.bearingX = bearingX;
					out.bearingY = bearingY;
					out.advance = advance;

					// Its empty, like space etc. we should allocate pixels tho? TODO
					if (spans.empty()) {
						return;
					}

					// build
					Rect rect(
						static_cast<float>(spans.front().x),
						static_cast<float>(spans.front().y),
						static_cast<float>(spans.front().x),
						static_cast<float>(spans.front().y)
						);

					for (auto& s : spans) {
						rect.include(sani::math::Vec2i(s.x, s.y));
						rect.include(sani::math::Vec2i(s.x + s.width - 1, s.y));
					}

					for (auto& s : outlineSpans) {
						rect.include(sani::math::Vec2i(s.x, s.y));
						rect.include(sani::math::Vec2i(s.x + s.width - 1, s.y));
					}



					// Get some metrics of our image.
					uint32 imgWidth = static_cast<uint32>(rect.width()),
						imgHeight = static_cast<uint32>(rect.height()),
						imgSize = imgWidth * imgHeight;

					PixelBitmapContent<sani::math::Vector4<unsigned char>>* pixels = new PixelBitmapContent<sani::math::Vector4<unsigned char>>(imgWidth, imgHeight);
					
					for (Span& s : spans) { // outlineSpans actually !!!!! TODO
						for (int w = 0; w < s.width; ++w) {
							int32 index = (int)((imgHeight - 1 - (s.y - rect.ymin)) * imgWidth + s.x - rect.xmin + w);
							pixels->setPixel(index, sani::math::Vector4<unsigned char>(255, 255, 255, s.coverage)); // white							
						}
					}
					pixels->flipVertical();
					out.pixels = pixels;
				}
				else {
					throw std::logic_error("not impl");
				}
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

			static uint32 calculateOutputWidth(const std::vector<Glyph>& glyphs) {
				return std::accumulate(glyphs.begin(), glyphs.end(), 0, [](uint32 r, const Glyph& g) {
					// TODO fix nullptr
					if (g.pixels == nullptr) return 0u;

					return 1 + r + g.pixels->getWidth() + 1;
				});
			}

			static uint32 calculateOutputHeight(const std::vector<Glyph>& glyphs) {
				// TODO max width shaiba
				return std::max_element(glyphs.begin(), glyphs.end(), [](const Glyph& a, const Glyph& b) {
					// TODO figure out something for these nullptrs
					if (a.pixels == nullptr) return true;
					else if (b.pixels == nullptr) return false;
					return a.pixels->getHeight() < b.pixels->getHeight();
				})->pixels->getHeight();
			}

			static BitmapContent* packGlyphs(std::vector<Glyph>& glyphs) {
				uint32 outputWidth = calculateOutputWidth(glyphs);
				uint32 outputHeight = calculateOutputHeight(glyphs);


				BitmapContent* bitmap = new PixelBitmapContent<sani::math::Vector4<unsigned char>>(outputWidth, outputHeight);

				uint32 xOffset = 0u;
				// TODO add max width
				uint32 yOffset = 0u;

				for (auto& glyph : glyphs) {
					BitmapContent* pixels = glyph.pixels;

					// white space and stuff
					if (pixels == nullptr) {
						glyph.source = math::Rect32i{ 0, 0, 0, 0 };
						continue;
					}

					uint32 width = pixels->getWidth();
					uint32 height = pixels->getHeight();
					sani::math::Rect32i source(0, 0, width, height);
					sani::math::Rect32i destination(1 + xOffset, yOffset, width, height);
					// TODO move this
					glyph.source = destination;
					bitmap->copyFrom(pixels, source, destination);
					xOffset += width;
				}

				return bitmap;

			}

			ResourceItem* SpriteFontProcessor::process(ResourceItem* input) {
				if (FT_Init_FreeType(&library)) {
					throw std::runtime_error("Failed to initialize freetype");
				}

				FontDescription* desc = static_cast<FontDescription*>(input);

				// import the actual font now
				FT_Face face = createFontFace(desc);
			
				const std::vector<unsigned short>& characters = desc->getCharacters();
				std::vector<Glyph> glyphs;
				glyphs.reserve(characters.size());

				for (auto character : characters) {
					Glyph glyph;
					importGlyph(desc, character, face, glyph);
					glyphs.push_back(glyph);
				}

				BitmapContent* bitmap = packGlyphs(glyphs);
				
				std::vector<GlyphContent> glyphContent;
				glyphContent.reserve(characters.size());
				for (auto& glyph : glyphs) {
					glyphContent.push_back(GlyphContent{
						glyph.character,
						glyph.source,
						glyph.bearingX,
						glyph.bearingY,
						glyph.advance
					});
				}

				// font height
				volatile float lineSpacing = static_cast<float>(face->size->metrics.height >> 6);

				SpriteFontContent* output = new SpriteFontContent(desc, bitmap, glyphContent, lineSpacing);

				FT_Done_Face(face);
				FT_Done_FreeType(library);

				return output;
			}
		}
	}
}