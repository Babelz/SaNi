#pragma once

#include "sani/core/logging/log.hpp"
#include "sani/graphics/renderables/text.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/sprite_font.hpp"
#include "sani/graphics/renderables/rectangle.hpp"

#include <algorithm>
#include <sstream>

namespace sani {

	namespace graphics {

		/*
			TODO: cleanup when it works...
		*/

		const uint32 TokenVerticesCount = 4;
		const uint32 TokenIndicesCount = 6;
		const uint32 TokenVertexElementsCount = 9;

		static void copyVertexData(Text& text) {
			uint32 vertexPointer = 0;

			for (uint32 i = 0; i < text.tokens.size(); i++) {
				text.renderData.vertices[vertexPointer++] = text.tokens[i].rect.renderData.vertices[0];
				text.renderData.vertices[vertexPointer++] = text.tokens[i].rect.renderData.vertices[1];
				text.renderData.vertices[vertexPointer++] = text.tokens[i].rect.renderData.vertices[2];
				text.renderData.vertices[vertexPointer++] = text.tokens[i].rect.renderData.vertices[3];
			}
		}
		static void generateIndices(Text& text) {
			const uint32 indicesCount = text.contents.size() * TokenIndicesCount;

			int32 vertexIndexPointer = 0;

			for (uint32 i = 0; i < indicesCount; i += TokenVerticesCount) {
				text.renderData.vertexIndices[vertexIndexPointer++] = i;
				text.renderData.vertexIndices[vertexIndexPointer++] = i + 1;
				text.renderData.vertexIndices[vertexIndexPointer++] = i + 2;

				text.renderData.vertexIndices[vertexIndexPointer++] = i + 1;
				text.renderData.vertexIndices[vertexIndexPointer++] = i + 3;
				text.renderData.vertexIndices[vertexIndexPointer++] = i + 2;
			}
		}

		static void resizeBuffers(Text& text) {
			text.tokens.resize(text.contents.size());

			const uint32 verticesCount = text.contents.size() * TokenVerticesCount;
			const uint32 indicesCount = text.contents.size() * TokenVertexElementsCount;

			text.renderData.vertices.resize(verticesCount);
			text.renderData.vertexIndices.resize(indicesCount);
		}

		static void updateTextRenderData(Text& text) {
			const uint32 verticesCount = text.contents.size() * TokenVerticesCount;
			const uint32 indicesCount = text.contents.size() * TokenVertexElementsCount;

			RenderElementData& textRenderData = text.renderData.renderElements[0];
			textRenderData.first = 0;
			textRenderData.last = verticesCount;
			textRenderData.vertexElements = 9;
			textRenderData.offset = 0;
			textRenderData.indices = indicesCount;

			text.renderData.renderElementsCount = 1;
		}
		static void generateTokens(Text& text) {
			uint32 tokenIndexPointer = 0;
			uint32 rowCounter = 0;
			uint32 columnCounter = 0;

			float32 mw = 0.0f;
			float32 mh = 0.0f;
			float32 xOffset = 0.0f;
			float32 yOffset = 0.0f;
			float32 spacing = 0.0f;

			for (auto ch : text.contents) {
				if (ch == '\r') continue;

				if (ch == '\n') {
					xOffset = 0.0f;
					yOffset += text.font->lineSpacing;

					columnCounter = 0;
					rowCounter++;

					continue;
				}

				auto it = std::find_if(text.font->characters.begin(), text.font->characters.end(), [ch](const uint32 rhs) {
					return ch == rhs;
				});

				if (it == text.font->characters.end()) {
					std::stringstream ss;
					ss << "character \"";
					ss << ch;
					ss << "\" ";
					ss << "not present in the sprite font";

					FNCLOG_ERR(log::OutFlags::All, ss.str());

					std::abort();
				}

				const uint32 glyphIndex = static_cast<uint32>(std::distance(text.font->characters.begin(), it));
				const resource::GlyphContent& glyph = text.font->glyphs[glyphIndex];

				const float32 x = xOffset + glyph.xOffset;
				const float32 y = yOffset - glyph.yOffset + spacing;
				const float32 w = static_cast<float32>(glyph.source.w);
				const float32 h = static_cast<float32>(glyph.source.h);

				const math::Rect32f source(static_cast<float32>(glyph.source.x),
										   static_cast<float32>(glyph.source.y),
										   static_cast<float32>(glyph.source.w),
										   static_cast<float32>(glyph.source.h));

				mw = mw < x + w ? x + w : mw;
				mh = mh < y + h ? y + h : mh;

				Token& token = text.tokens[tokenIndexPointer++];
				token.rect = Rectangle(x + text.transform.position.x, y + text.transform.position.y, w, h);
				token.rect.transform.origin.x = 0.0f;
				token.rect.transform.origin.y = 0.0f;
				token.rect.texture = text.font->texture;
				token.rect.textureSource = source;
				token.rect.fill = text.color;
				
				token.localPosition.x = x;
				token.localPosition.y = y;

				token.column = columnCounter;
				token.row = rowCounter;
				token.ch = ch;
				
				recomputeVertices(token.rect);
				recomputeBounds(token.rect);
				updateRenderData(token.rect);

				xOffset += glyph.xAdvance;

				columnCounter++;
			}

			text.localBounds.w = mw;
			text.localBounds.h = mh;

			text.transform.origin.x = mw / 2.0f;
			text.transform.origin.y = mh / 2.0f;
		}

		void setText(Text& text, const String16& contents, const Color& color) {
			text.contents = contents;
			text.color = color;

			resizeBuffers(text);

			updateTextRenderData(text);

			generateTokens(text);

			copyVertexData(text);

			generateIndices(text);

			updateRenderData(text);
		}

		void recomputeVertices(Text& text) {
			for (auto& token : text.tokens) {
				Transform& transform = token.rect.transform;
				
				transform.rotation = token.localRotation + text.transform.rotation;
				transform.scale.x = token.localScale.x * text.transform.scale.y;
				transform.scale.y = token.localScale.y * text.transform.scale.y;

				const float32 rotatedX = ((token.localPosition.x * transform.scale.x - text.transform.origin.x) * math::cos(text.transform.rotation)) - 
										 ((token.localPosition.y * transform.scale.y - text.transform.origin.y) * math::sin(text.transform.rotation));
				
				const float32 rotatedY = ((token.localPosition.x * transform.scale.x - text.transform.origin.x) * math::sin(text.transform.rotation)) + 
										 ((token.localPosition.y * transform.scale.y - text.transform.origin.y) * math::cos(text.transform.rotation));

				transform.position.x = text.transform.position.x + rotatedX;
				transform.position.y = text.transform.position.y + rotatedY;

				recomputeVertices(token.rect);
			}

			copyVertexData(text);
		}
		void recomputeBounds(Text& text) {
			float32 mw = 0.0f;
			float32 mh = 0.0f;

			for (auto& token : text.tokens) {
				recomputeBounds(token.rect);

				mw = mw < token.localPosition.x + token.rect.localBounds.w ? token.localPosition.x + token.rect.localBounds.w : mw;
				mh = mh < token.localPosition.y + token.rect.localBounds.h ? token.localPosition.y + token.rect.localBounds.h : mh;
			}

			text.localBounds.w = mw;
			text.localBounds.h = mh;

			text.globalBounds.x = text.transform.position.x;
			text.globalBounds.y = text.transform.position.y;
			text.globalBounds.w = mw * text.transform.scale.x;
			text.globalBounds.h = mh * text.transform.scale.y;
		}

		void updateRenderData(Text& text) {
			text.texture = text.font->texture;

			text.renderData.renderElements[0].texture = text.texture->getID();

			updateGroupIdentifier(text);

			for (auto& token : text.tokens) updateRenderData(token.rect);
		}
	}
}