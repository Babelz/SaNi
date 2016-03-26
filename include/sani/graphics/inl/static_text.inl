#pragma once

#include "sani/platform/graphics/screen_shader_source.hpp"
#include "sani/core/math/matrix4.hpp"
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
#include "sani/graphics/renderables/rectangle.hpp"
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

			staticText.color = color;

			// Generate text vertices.
			// We will render the generated vertices once to the text
			// render target and dispose them.
			// Text will continue using the same render target
			// until this function gets called again.
			const uint32 TokenVerticesCount = 4;
			const uint32 TokenIndicesCount = 6;
			const uint32 TokenVertexElementsCount = 9;

			std::vector<VertexPositionColorTexture> vertices;
			std::vector<uint32> indices;

			vertices.resize(text.size() * TokenVerticesCount);
			indices.resize(text.size() * TokenVertexElementsCount);

			resource::SpriteFont* const font = staticText.font;

			const float32 spacing = staticText.font->lineSpacing;
			float32 xOffset = 0.0f;
			float32 yOffset = 0.0f;
			
			// Used to create the render target.
			float32 targetAreaWidth = 0.0f;
			float32 targetAreaHeight = 0.0f;
			
			// Generate indices.
			const uint32 indicesCount = text.size() * TokenIndicesCount;
			int32 vertexIndexPointer = 0;
			for (uint32 i = 0; i < indicesCount; i += TokenVerticesCount) {
				indices[vertexIndexPointer++] = i;
				indices[vertexIndexPointer++] = i + 1;
				indices[vertexIndexPointer++] = i + 2;

				indices[vertexIndexPointer++] = i + 1;
				indices[vertexIndexPointer++] = i + 3;
				indices[vertexIndexPointer++] = i + 2;
			}

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
					const math::Rect32f source = math::Rect32f(static_cast<float32>(glyph.source.x),
															   static_cast<float32>(glyph.source.y),
															   static_cast<float32>(glyph.source.w),
															   static_cast<float32>(glyph.source.h));

					graphics::Rectangle rectangle(x, y, w, h);
					rectangle.texture = font->texture;
					rectangle.fill = color::Red;
					rectangle.borderFill = color::Green;
					rectangle.transform.origin.x = 0.0f;
					rectangle.transform.origin.y = 0.0f;
					rectangle.borderThickness = 10.0f;
					rectangle.textureSource = source;
					
					recomputeVertices(rectangle);
					recomputeBounds(rectangle);
					updateRenderData(rectangle);

					targetAreaWidth = targetAreaWidth < rectangle.globalBounds.right() ? rectangle.globalBounds.right() : targetAreaWidth;
					targetAreaHeight = targetAreaHeight < rectangle.globalBounds.bottom() ? rectangle.globalBounds.bottom() : targetAreaHeight;

					for (auto& vpct : rectangle.renderData.vertices) vertices.push_back(vpct);
					
					xOffset += glyph.xAdvance;
					break;
				}
			}

			targetAreaWidth = 1280;
			targetAreaHeight = 720;

			staticText.localBounds.w = targetAreaWidth;
			staticText.localBounds.h = targetAreaHeight;


			GraphicsDevice* const graphicsDevice = staticText.graphicsDevice;

			// Do render target checks.
			// TODO: automatic?...
			const uint32 uwidth = static_cast<uint32>(staticText.globalBounds.w);
			const uint32 uheight = static_cast<uint32>(staticText.globalBounds.h);

			if (staticText.renderTarget != nullptr) {
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

			staticText.renderTarget->setClearColor(101.f / 255, 156.f / 255, 239.f / 255, 1.0f);

			recomputeBounds(staticText);

			const math::Vec3f npos(-0.0f, 0.0f, 0.0f);
			const Viewport viewport(0, 0, staticText.globalBounds.w, staticText.globalBounds.h);
/*
			transform = math::ortho<float32>(0.0f, static_cast<float32>(viewport.width), static_cast<float32>(viewport.height), 0.0f, zNear, zFar);
			transform = math::translate(transform, npos) * transform;
			transform = math::rotate(transform, rotation, math::Vec3f(0.0f, 0.0f, 1.0f));
			transform = math::scale(transform, zoom);
			transform = math::translate(transform, origin) * transform;*/

			auto ortho = math::ortho<float32>(0.0f, static_cast<float32>(viewport.width), static_cast<float32>(viewport.height), 0.0f, 0.1f, 100.0f);
			ortho = math::translate(ortho, npos) * ortho;

			GraphicsEffect effect = GraphicsEffect::compile(graphicsDevice, DefaultTexturedPolygonVertexSource, DefaultTexturedPolygonFragmentSource);
			EffectUniform* transform = effect.findUniform("transform");
			transform->setData(&ortho);

			TexturedPolygonRenderSetup rendersetup(graphicsDevice);
			rendersetup.setVertexElementsCount(9);

			graphicsDevice->saveState();
			graphicsDevice->setViewport(viewport);
			graphicsDevice->setRenderTarget(staticText.renderTarget);
			graphicsDevice->bindTexture(font->texture->getID());
			SANI_ASSERT(!graphicsDevice->hasErrors());

			rendersetup.use();
			effect.bind();

			uint32 vertexBuffer = 0;
			uint32 indexBuffer = 0;
			uint32 vertexArray = 0;
			
			glGenVertexArrays(1, &vertexArray);
			glBindVertexArray(vertexArray);

			graphicsDevice->generateBuffer(vertexBuffer);
			graphicsDevice->bindBuffer(vertexBuffer, BufferType::ArrayBuffer);
			graphicsDevice->setBufferData(BufferType::ArrayBuffer, sizeof(float32) * vertices.size(), vertices.data(), BufferUsage::Static);
			SANI_ASSERT(!graphicsDevice->hasErrors());
			
			graphicsDevice->generateBuffer(indexBuffer);
			graphicsDevice->bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);
			graphicsDevice->setBufferData(BufferType::ElementArrayBuffer, sizeof(uint32) * indices.size(), indices.data(), BufferUsage::Static);
			SANI_ASSERT(!graphicsDevice->hasErrors());

			graphicsDevice->drawElements(RenderMode::Triangles, PrimitiveType::UInt, indices.size(), 0);
			SANI_ASSERT(!graphicsDevice->hasErrors());

			rendersetup.clear();
			effect.unbind();

			// Resume last device state.
			graphicsDevice->resumeState();

			// Set texture.
			staticText.texture = staticText.renderTarget;
			
			//staticText.renderData.renderElements[0].texture = font->texture->getID();
	
			recomputeVertices(staticText);
			recomputeBounds(staticText);
			updateRenderData(staticText);
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