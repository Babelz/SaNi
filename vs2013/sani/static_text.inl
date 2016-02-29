#pragma once

#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderables/static_text.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/sprite_font.hpp"
#include "sani/graphics/vertex_helper.hpp"

#include <algorithm>

namespace sani {

	namespace graphics {

		void setText(StaticText& staticText, const String16& text, const Color& color) {
			if (text.empty()) return;

			if (staticText.renderTarget.empty()) {
				staticText.renderTarget = RenderTarget2D(staticText.device, 
														 static_cast<uint32>(staticText.localBounds.w),
														 static_cast<uint32>(staticText.localBounds.h));
			}

			// Generate text vertices.
			// We will render the generated vertices once to the text
			// render target and dispose them.
			// Text will continue using the same render target
			// until this function gets called again.
			const uint32 TokenVerticesCount = 4;
			const uint32 TokenIndicesCount = 6;

			std::vector<VertexPositionColorTexture> vertices;
			std::vector<uint32> indices;

			vertices.reserve(text.size() * TokenVerticesCount);
			indices.reserve(text.size() * TokenIndicesCount);

			resource::SpriteFont* const font = staticText.font;

			const float32 spacing = staticText.font->lineSpacing;
			float32 xOffset = 0.0f;
			float32 yOffset = 0.0f;
			
			// Vertex pointer, index pointer and 
			// index counter.
			uint32 vp = 0;
			uint32 ip = 0;
			uint32 ic = 0;

			for (uint32 i = 0; i < text.size(); i++) {
				const uint32 ch = static_cast<uint32>(text[i]);

				switch (ch) {
				case '\r':
					continue;
				case '\n':
					xOffset = 0.0f;
					yOffset += spacing;
					continue;
				default:

					auto it = std::find_if(font->characters.begin(), font->characters.end(), [ch](const uint32 rhs) {
						return ch == rhs;
					});

					if (it == font->characters.end())throw std::runtime_error("character not present in sprite font");

					const uint32 index = std::distance(font->characters.begin(), it);
					
					const resource::GlyphContent& glyph = font->glyphs[index];
					const float32 x = xOffset + glyph.xOffset;
					const float32 y = yOffset - glyph.yOffset + spacing;
					const float32 w = static_cast<float32>(glyph.source.w);
					const float32 h = static_cast<float32>(glyph.source.h);
					const math::Rect32f source = math::Rect32f(x, y, w, h);

					// Create vertices.
					// Top-left.
					vertices[vp].vertexPositionColor.position.x	= x;
					vertices[vp].vertexPositionColor.position.y	= y;
					vertices[vp].vertexPositionColor.color		= staticText.color;
					vp++;

					// Top-right.
					vertices[vp].vertexPositionColor.position.x	= x + w;
					vertices[vp].vertexPositionColor.position.y	= y;
					vertices[vp].vertexPositionColor.color		= staticText.color;
					vp++;

					// Bottom-left.
					vertices[vp].vertexPositionColor.position.x	= x;
					vertices[vp].vertexPositionColor.position.y	= y + h;
					vertices[vp].vertexPositionColor.color		= staticText.color;
					vp++;

					// Bottom-right.
					vertices[vp].vertexPositionColor.position.x	= x + w;
					vertices[vp].vertexPositionColor.position.y	= y + h;
					vertices[vp].vertexPositionColor.color		= staticText.color;
					vp++;

					// Create indices.
					indices[ip++] = ic;
					indices[ip++] = ic + 1;
					indices[ip++] = ic + 2; 

					indices[ip++] = ic + 1;
					indices[ip++] = ic + 3;
					indices[ip++] = ic + 2;

					ic += TokenIndicesCount;

					// Compute texture coordinates.
					VertexPositionColorTexture* vertices[] {
						vertices[vp - 3],	// Top-left.
						vertices[vp - 2],	// Top-right.
						vertices[vp - 1],	// Bottom-left.
						vertices[vp],		// Bottom-right.
					};

					computeRectangleTextureCoordinates(vertices, 
													   source, 
													   static_cast<float32>(font->texture->getWidth()), 
													   static_cast<float32>(font->texture->getHeight()));
					break;
				}
			}

			GraphicsDevice* const device = staticText.device;

			// Save device state.
			// TODO: save device state

			// Create buffers.
			uint32 vertexBuffer = 0;
			uint32 indexBuffer = 0;

			device->generateBuffer(vertexBuffer);
			device->generateBuffer(indexBuffer);

			// Setup device for rendering.

			// Render to render target.

			// Resume last device state.
			// TODO: resume last device state
 		}

		void recomputeVertices(StaticText& staticText) {
		}
		void recomputeBounds(StaticText& staticText) {
		}

		void updateRenderData(StaticText& staticText) {
		}
	}
}