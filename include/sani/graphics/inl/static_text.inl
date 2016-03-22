#pragma once

#include "sani/core/logging/log.hpp"
#include "sani/graphics/camera2d.hpp"
#include "sani/graphics/setups/textured_polygon_render_setup.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/graphics/default_shader_sources.hpp"
#include "sani/graphics/graphics_effect.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderables/static_text.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/sprite_font.hpp"
#include "sani/graphics/vertex_helper.hpp"

#include <algorithm>
#include <sstream>

namespace sani {

	namespace graphics {

		/*
			TODO: cleanup when it works...
		*/

		void setText(StaticText& staticText, const String16& text, const Color& color) {
			if (text.empty()) return;

			// Generate text vertices.
			// We will render the generated vertices once to the text
			// render target and dispose them.
			// Text will continue using the same render target
			// until this function gets called again.
			const uint32 TokenVerticesCount = 4;
			const uint32 TokenIndicesCount = 6;

			std::vector<VertexPositionColorTexture> vertices;
			std::vector<uint32> indices;

			vertices.resize(text.size() * TokenVerticesCount);
			indices.resize(text.size() * TokenIndicesCount);

			resource::SpriteFont* const font = staticText.font;

			const float32 spacing = staticText.font->lineSpacing;
			float32 xOffset = 0.0f;
			float32 yOffset = 0.0f;
			
			// Used to create the render target.
			float32 targetAreaWidth = 800.f;
			float32 targetAreaHeight = 600.f;
			
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

					if (it == font->characters.end()) {
						std::stringstream ss;
						ss << "character \"";
						ss << ch;
						ss << "\" ";
						ss << "not present in the sprite font";

						FNCLOG_ERR(log::OutFlags::All, ss.str());

						std::abort();
					}

					const uint32 index = static_cast<uint32>(std::distance(font->characters.begin(), it));
					const resource::GlyphContent& glyph = font->glyphs[index];

					const float32 x = xOffset + glyph.xOffset;
					const float32 y = yOffset - glyph.yOffset + spacing;
					const float32 w = static_cast<float32>(glyph.source.w);
					const float32 h = static_cast<float32>(glyph.source.h);
					const math::Rect32f source = math::Rect32f((float32)glyph.source.x, (float32)glyph.source.y, (float32)glyph.source.w, (float32)glyph.source.h);

					// Update area variables.
					//targetAreaWidth += x + w;
					//targetAreaHeight = targetAreaHeight < y ? y : targetAreaHeight;

					// Create vertices.
					// Top-left.
					vertices[vp].vertexPositionColor.position.x	= x;
					vertices[vp].vertexPositionColor.position.y	= y;
					vertices[vp].vertexPositionColor.color		= color;
					vp++;

					// Top-right.
					vertices[vp].vertexPositionColor.position.x	= x + w;
					vertices[vp].vertexPositionColor.position.y	= y;
					vertices[vp].vertexPositionColor.color		= color;
					vp++;

					// Bottom-left.
					vertices[vp].vertexPositionColor.position.x	= x;
					vertices[vp].vertexPositionColor.position.y	= y + h;
					vertices[vp].vertexPositionColor.color		= color;
					vp++;

					// Bottom-right.
					vertices[vp].vertexPositionColor.position.x	= x + w;
					vertices[vp].vertexPositionColor.position.y	= y + h;
					vertices[vp].vertexPositionColor.color		= color;
					vp++;

					// Create indices.
					indices[ip++] = ic;
					indices[ip++] = ic + 1;
					indices[ip++] = ic + 2; 

					indices[ip++] = ic + 1;
					indices[ip++] = ic + 3;
					indices[ip++] = ic + 2;

					ic += TokenVerticesCount;

					// Compute texture coordinates.
					VertexPositionColorTexture* tokenVertices[] {
						&vertices[vp - 3],	// Top-left.
						&vertices[vp - 2],	// Top-right.
						&vertices[vp - 1],	// Bottom-left.
						&vertices[vp],		// Bottom-right.
					};

					computeRectangleTextureCoordinates(tokenVertices,
													   source, 
													   static_cast<float32>(font->texture->getWidth()), 
													   static_cast<float32>(font->texture->getHeight()));

					xOffset += glyph.xAdvance;
					break;
				}
			}

			GraphicsDevice* const graphicsDevice = staticText.graphicsDevice;

			// Do render target checks.
			// TODO: automatic?...
			const uint32 uwidth = static_cast<uint32>(targetAreaWidth);
			const uint32 uheight = static_cast<uint32>(targetAreaHeight);

			if (staticText.renderTarget != nullptr) {
				// TODO: resize on smaller on neq?
				if (staticText.renderTarget->getWidth() != uwidth || staticText.renderTarget->getHeight() != uheight) {
					staticText.renderTarget->dispose();

					if (!staticText.renderTarget->disposed()) {
						FNCLOG_ERR(log::OutFlags::All, "could not dispose render target");

						std::abort();
					}

					delete staticText.renderTarget;
					
					staticText.renderTarget = nullptr;
				}
			}

			if (staticText.renderTarget == nullptr) 
				staticText.renderTarget = new RenderTarget2D(graphicsDevice, static_cast<uint32>(targetAreaWidth), static_cast<uint32>(targetAreaHeight));

			// Save device state.
			//graphicsDevice->saveState();

			// Create buffers.
			uint32 vertexBuffer = 0;
			uint32 indexBuffer = 0;

			graphicsDevice->generateBuffer(vertexBuffer);
			graphicsDevice->generateBuffer(indexBuffer);
			graphicsDevice->bindBuffer(vertexBuffer, BufferType::ArrayBuffer);
			graphicsDevice->bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

			graphicsDevice->setBufferData(BufferType::ArrayBuffer,
										  static_cast<uint32>(vertices.size() * sizeof(float32) * sizeof(VertexPositionColorTexture)),
										  vertices.data(),
										  BufferUsage::Static);


			graphicsDevice->setBufferData(BufferType::ElementArrayBuffer,
										  static_cast<uint32>(indices.size() * sizeof(uint32)),
										  indices.data(),
										  BufferUsage::Static);

			// Use default effect while rendering to render target.
			GraphicsEffect shader = GraphicsEffect::compile(graphicsDevice, DefaultTexturedPolygonVertexSource, DefaultTexturedPolygonFragmentSource);

			TexturedPolygonRenderSetup renderSetup(graphicsDevice);

			graphicsDevice->setRenderTarget(staticText.renderTarget);

			// Render to render target.
			graphicsDevice->bindTexture(staticText.font->texture->getID());

			renderSetup.setVertexElementsCount(9);

			renderSetup.use();
			shader.bind();

			Camera2D c(graphicsDevice->getViewport());
			c.computeTransformation();
			auto t = c.transformation();

			EffectUniform* f = shader.findUniform("transform");
			f->setData(&t);

			graphicsDevice->drawElements(RenderMode::Triangles, PrimitiveType::UInt, static_cast<uint32>(indices.size()), 0);

			renderSetup.clear();
			shader.unbind();

			// Delete buffers.
			graphicsDevice->unbindBuffer(BufferType::ArrayBuffer);
			graphicsDevice->unbindBuffer(BufferType::ElementArrayBuffer);
			graphicsDevice->deleteBuffer(vertexBuffer);
			graphicsDevice->deleteBuffer(indexBuffer);

			// Resume last device state.
			//graphicsDevice->resumeState();

			// Set texture.
			staticText.texture = staticText.renderTarget;
 		}

		void recomputeVertices(StaticText& staticText) {
			const math::Vec3f& position = staticText.transform.position;
			const math::Vec3f& origin = staticText.transform.origin;
			const math::Vec3f& scale = staticText.transform.scale;
			const math::Rect32f& localBounds = staticText.localBounds;
			const float32 rotation = staticText.transform.rotation;

			const float32 sin = math::sin(rotation);
			const float32 cos = math::cos(rotation);

			const float32 dx = -origin.x * scale.x;
			const float32 dy = -origin.y * scale.y;

			VertexPositionColorTexture* shapeVertices[] {
				&staticText.renderData.vertices[0],
					&staticText.renderData.vertices[1],
					&staticText.renderData.vertices[2],
					&staticText.renderData.vertices[3]
			};

			math::Vec3f shapeGlobalPositions[] {
				position,
					position,
					position,
					position
			};

			math::Vec3f shapeVertexPositions[] {
				math::Vec3f(0.0f, 0.0f, 0.0f),								// Top left
					math::Vec3f(localBounds.w, 0.0f, 0.0f) * scale,				// Top right
					math::Vec3f(0.0f, localBounds.h, 0.0f) * scale,				// Bottom left
					math::Vec3f(localBounds.w, localBounds.h, 0.0f) * scale		// Bottom right
			};

			applyRotationToRectangle(shapeGlobalPositions, shapeVertexPositions, dx, dy, sin, cos);

			for (uint32 i = 0; i < 4; i++) {
				shapeVertices[i]->vertexPositionColor.position = shapeGlobalPositions[i];
				shapeVertices[i]->vertexPositionColor.color = staticText.color;
			}
		}
		void recomputeBounds(StaticText& staticText) {
			const math::Vec3f& position = staticText.transform.position;
			const math::Vec3f& scale = staticText.transform.scale;

			staticText.globalBounds.x = position.x;
			staticText.globalBounds.y = position.y;
			staticText.globalBounds.w = staticText.localBounds.w * scale.x;
			staticText.globalBounds.h = staticText.localBounds.h * scale.y;
		}

		void updateRenderData(StaticText& staticText) {
			staticText.renderData.renderElements[0].texture = staticText.texture->getID();

			VertexPositionColorTexture* vertices[] {
				&staticText.renderData.vertices[0],
					&staticText.renderData.vertices[1],
					&staticText.renderData.vertices[2],
					&staticText.renderData.vertices[3]
			};

			if (!staticText.textureSource.isEmpty()) {
				computeRectangleTextureCoordinates(vertices,
					staticText.textureSource,
					static_cast<float32>(staticText.texture->getWidth()),
					static_cast<float32>(staticText.texture->getHeight()));
			}
			else {
				applyDefaultRectangleTextureCoordinates(vertices);
			}

			updateGroupIdentifier(staticText);
		}
	}
}