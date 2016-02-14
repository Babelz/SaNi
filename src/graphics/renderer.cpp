#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/setups/render_setups.hpp"
#include "sani/graphics/render_batch.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/core/memory/memory.hpp"

namespace sani {

	namespace graphics {

		const static int32 InitialBufferSize = BLOCK_1024KB / sizeof(float32);
		const static int32 InitialRenderBatchesCount = 32;
		const static int32 InitialIndexTransformBufferSize = 32;
		
		// For starters, reserve 1024kb worth of vertex memory.
		// Keep the buffer usage as dynamic (max RAM as the limit).

		Renderer::Renderer(GraphicsDevice* const graphicsDevice) : graphicsDevice(graphicsDevice),
																   vertices(InitialBufferSize, BufferSizing::Dynamic),
																   indices(InitialBufferSize, BufferSizing::Dynamic),
																   verticesSize(InitialBufferSize),
																   indicesSize(InitialBufferSize),
																   vertexBuffer(0),
																   indexBuffer(0),
																   texture(0),
																   renderBatchesCount(0),
																   renderBatcher(defaultEffects, RenderStatesCount) {
			renderBatches.resize(InitialRenderBatchesCount);
			indexTransformBuffer.resize(InitialIndexTransformBufferSize);
		}

		void Renderer::generateDefaultShaders() {
			/*
				Default polygon shader sources.

				TODO: move to somewhere else when the content can load effects
				and the effect class has been implemented.
			*/

			/*
				TODO: as we have some major problems with AMD graphics adapters
				while the engine is running under GL 2.1, we just "force"
				the engine to use GL version 3.3 while running under Windows
				or Linux.

				Fix this by using the contents effects files so that there are
				GL 3.3 and 2.1 default effects.
			*/

			const char* const defaultPolygonVertexSource = 
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX || SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
											"#version 330\n"
											""
											"layout(location = 0) in vec3 vertex_position;"
											"layout(location = 1) in vec4 vertex_color;"
											""
											"out vec4 out_vertex_color;"
											"uniform mat4 transform;"
#elif
											"#version 120\n"
											""
											"attribute vec3 vertex_position;"
											"attribute vec4 vertex_color;"
											""
											"varying vec4 out_vertex_color;"
											"uniform mat4 transform;"
#endif
											"void main() {"
											"	gl_Position = transform * vec4(vertex_position, 1.0);"
											"	out_vertex_color = vertex_color;"
											"}";

			const char* const defaultPolygonFragmentSource = 
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX || SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
											"#version 330\n"
											""
											"in vec4 out_vertex_color;"
#elif
											"#version 120\n"
											""
											"varying vec4 out_vertex_color;"
#endif
											"void main() {"
											"  gl_FragColor = out_vertex_color;"
											"}";

			const char* const defaultTexturedPolygonVertexSource = 
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX || SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
											"#version 330\n"
											""
											"layout(location = 0) in vec3 vertex_position;"
											"layout(location = 1) in vec4 vertex_color;"
											"layout(location = 2) in vec2 texture_coordinates;"
											""
											"out vec2 out_texture_coordinates;"
											"out vec4 out_vertex_color;"
											""
											"uniform mat4 transform;"
#elif
											"#version 120\n"
											""
											"attribute vec3 vertex_position;"
											"attribute vec4 vertex_color;"
											"attribute vec2 texture_coordinates;"
											""
											"varying vec2 out_texture_coordinates;"
											"varying vec4 out_vertex_color;"
											""
											"uniform mat4 transform;"
#endif
											"void main() {"
											"	gl_Position = transform * vec4(vertex_position, 1.0);"
											"	out_texture_coordinates = texture_coordinates;"
											"	out_vertex_color = vertex_color;"
											"}";

			const char* const defaultTexturedPolygonFragmentSource =
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX || SANI_PLATFORM_WIN32
											"#version 330\n"
											""
											"in vec2 out_texture_coordinates;"
											"in vec4 out_vertex_color;"
											""
											"uniform sampler2D sampler;"
#elif
											"#version 120\n"
											""
											"varying vec2 out_texture_coordinates;"
											"varying vec4 out_vertex_color;"
											""
											"uniform sampler2D sampler;"
#endif
											"void main() {"
											"	gl_FragColor = texture2D(sampler, out_texture_coordinates) * out_vertex_color;"
											"}";

			defaultEffects[static_cast<uint32>(RenderState::Waiting)]			= GraphicsEffect();
			defaultEffects[static_cast<uint32>(RenderState::Polygons)]			= GraphicsEffect::compile(graphicsDevice, defaultPolygonVertexSource, defaultPolygonFragmentSource);
			defaultEffects[static_cast<uint32>(RenderState::TexturedPolygons)]  = GraphicsEffect::compile(graphicsDevice, defaultTexturedPolygonVertexSource, defaultTexturedPolygonFragmentSource);
		}
		void Renderer::generateRenderSetups() {
			renderSetups[static_cast<uint32>(RenderState::Waiting)]				= nullptr;
			renderSetups[static_cast<uint32>(RenderState::Polygons)]			= new PolygonRenderSetup(graphicsDevice);
			renderSetups[static_cast<uint32>(RenderState::TexturedPolygons)]	= new TexturedPolygonRenderSetup(graphicsDevice);
		}
		void Renderer::generateBuffers() {
			graphicsDevice->generateBuffer(vertexBuffer);
			graphicsDevice->bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

			graphicsDevice->generateBuffer(indexBuffer);
			graphicsDevice->bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

			graphicsDevice->setBufferData(BufferType::ArrayBuffer,
										  vertices.getSize() * sizeof(float32),
										  vertices.data(),
										  BufferUsage::Dynamic);


			graphicsDevice->setBufferData(BufferType::ElementArrayBuffer,
										  indices.getSize() * sizeof(uint32),
										  indices.data(),
										  BufferUsage::Dynamic);
		}

		void Renderer::updateVertexBufferSize() {
			// Rebind buffer if it's size has changed.
			if (verticesSize != vertices.getSize()) {
				graphicsDevice->bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

				graphicsDevice->setBufferData(BufferType::ArrayBuffer,
											 vertices.getSize() * sizeof(float32),
											 vertices.data(),
											 BufferUsage::Dynamic);

				verticesSize = vertices.getSize();
			}
		}
		void Renderer::updateIndexBufferSize() {
			if (indicesSize != indices.getSize()) {
				graphicsDevice->bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

				graphicsDevice->setBufferData(BufferType::ElementArrayBuffer,
											 indices.getSize() * sizeof(uint32),
											 indices.data(),
											 BufferUsage::Dynamic);

				indicesSize = indices.getSize();
			}
		}

		void Renderer::applyVertexOffset() {
			const uint32 nextOffset = renderBatcher.getNextOffset();

			if (nextOffset > 0) vertices.offset(nextOffset);
		}

		void Renderer::copyVertexData(const RenderElementData* const renderElementData, const RenderData* const renderData) {
			const uint32 elementVertexElementsCount		 = renderElementData->vertexElements;
			const uint32 vertexElementOffset			 = renderElementData->offset;

			const uint32 first							 = renderElementData->first;
			const uint32 last							 = renderElementData->last + 1;

			const uint32 firstVertexElement				 = first * (elementVertexElementsCount + vertexElementOffset);
			const uint32 lastVertexElement				 = last * (elementVertexElementsCount + vertexElementOffset);

			const uint32 vertexElementsCount			 = lastVertexElement - firstVertexElement;
			const uint32 verticesCount					 = last - first;
			
			const float32* const vertexElementsData		 = reinterpret_cast<const float32* const>(renderData->vertices.data());
			
			uint32 vertexElementPointer					 = firstVertexElement;
			
			if (vertexElementOffset != 0) {
				uint32 vertexElementPointer = firstVertexElement;

				for (uint32 i = 0; i < verticesCount; i++) {
					vertices.push(&vertexElementsData[vertexElementPointer], elementVertexElementsCount);

					vertexElementPointer += elementVertexElementsCount + vertexElementOffset;
				}
			} else {
				vertices.push(&vertexElementsData[firstVertexElement], vertexElementsCount);
			}
		}
		void Renderer::copyIndexData(const RenderElementData* const renderElementData, const RenderData* const renderData) {
			const uint32 indicesCount					= renderElementData->indices;
			const uint32* indicesData					= reinterpret_cast<const uint32*>(renderData->vertexIndices.data());

			const uint32 elementVertexElementsCount		= renderElementData->vertexElements;
			const uint32 bufferVertexElementsCount		= vertices.getElementsCount() / elementVertexElementsCount;
			const uint32 vertexOffset					= bufferVertexElementsCount - (renderElementData->last + 1 - renderElementData->first);

			if (indexTransformBuffer.size() < indicesCount) indexTransformBuffer.resize(indexTransformBuffer.size() + indicesCount);

			for (uint32 i = 0; i < indicesCount; i++) indexTransformBuffer[i] = indicesData[i] + vertexOffset;

			indices.push(indexTransformBuffer.data(), indicesCount);
		}

		void Renderer::flushRenderBatch(const RenderBatch* const renderBatch) {
			if (renderBatch->elementsData == nullptr) return;

			const VertexMode vertexMode = renderBatch->vertexMode;
			const RenderMode renderMode = renderBatch->renderMode;

			RenderSetup* const renderSetup = renderSetups[renderBatch->renderSetup];
			renderSetup->setVertexElementsCount(renderBatch->elementsData->vertexElements);
			renderSetup->use();
			
			graphicsDevice->bindTexture(renderBatch->texture);
			graphicsDevice->useProgram(renderBatch->effect);

			if (vertexMode == VertexMode::NoIndexing)	graphicsDevice->drawArrays(renderMode, renderBatch->verticesBegin, renderBatch->verticesCount);
			else										graphicsDevice->drawElements(renderMode, PrimitiveType::UInt, renderBatch->indicesCount, renderBatch->indicesBegin);

			renderSetup->clear();

			graphicsDevice->bindTexture(0);
			graphicsDevice->useProgram(0);
		}

		void Renderer::checkBatchEffects() {
			for (uint32 i = 0; i < renderBatchesCount; i++) {
				RenderBatch& renderBatch = renderBatches[i];
				
				renderBatch.effect = renderBatch.effect <= 2 ? defaultEffects[renderBatch.effect].getEffect() : renderBatch.effect;
			}
		}
		void Renderer::updateBufferDatas() {
			updateVertexBufferSize();
			updateIndexBufferSize();

			graphicsDevice->bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

			graphicsDevice->setBufferSubData(BufferType::ArrayBuffer,
											 0,
											 vertices.getElementsCount() * sizeof(float32),
											 vertices.data());

			if (indices.getElementsCount() > 0) {
				graphicsDevice->bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

				graphicsDevice->setBufferSubData(BufferType::ElementArrayBuffer,
											 	 0,
												 indices.getElementsCount() * sizeof(uint32),
												 indices.data());
			}
		}

		void Renderer::prepareRendering() {
			renderBatcher.prepareBatching(&renderBatches);

			vertices.resetBufferPointer();
			indices.resetBufferPointer();
		}

		bool Renderer::initialize() {
			generateDefaultShaders();
			generateRenderSetups();
			generateBuffers();

			return graphicsDevice->hasErrors();
		}

		void Renderer::beginRendering(const math::Mat4f& transform) {
			// Set default effects transform uniform values.
			defaultEffects[1].findUniform("transform")->setData((void*)&transform);
			defaultEffects[2].findUniform("transform")->setData((void*)&transform);

			prepareRendering();
		}

		void Renderer::renderElement(const Renderable* const renderable) {
			if (!renderable->visible) return;

			elementsCount = renderable->renderData.renderElementsCount;

			for (elementCounter = 0; elementCounter < elementsCount; elementCounter++) {
				const uint32 renderElementIndex						= renderable->renderData.renderElementIndices[elementCounter];
				const RenderElementData* const renderElementData	= &renderable->renderData.renderElements[renderElementIndex];

				renderBatcher.batchElement(renderElementData, elementCounter, elementsCount);
				
				applyVertexOffset();

				copyVertexData(renderElementData, &renderable->renderData);
				copyIndexData(renderElementData, &renderable->renderData);
			}
		}

		void Renderer::endRendering() {
			renderBatchesCount = renderBatcher.getRenderBatchesCount();

			checkBatchEffects();
			updateBufferDatas();

			for (uint32 i = 0; i < renderBatchesCount; i++) flushRenderBatch(&renderBatches[i]);
		}

		Renderer::~Renderer() {
			for (uint32 i = 0; i < RenderStatesCount; i++) delete renderSetups[i];
		}
	}
}