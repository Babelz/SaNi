#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/setups/render_setups.hpp"
#include "sani/graphics/render_batch.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		#define INITIAL_BUFFER_ELEMENTS_COUNT 32768
		
		// For starters, reserve 128kb worth of vertex memory (32768 float32 elements).
		// Keep the buffer usage as dynamic (memory as the limit).

		Renderer::Renderer(GraphicsDevice* const graphicsDevice) : graphicsDevice(graphicsDevice),
																  vertices(INITIAL_BUFFER_ELEMENTS_COUNT, BufferSizing::Dynamic),
																  indices(INITIAL_BUFFER_ELEMENTS_COUNT, BufferSizing::Dynamic),
																  verticesSize(INITIAL_BUFFER_ELEMENTS_COUNT),
																  indicesSize(INITIAL_BUFFER_ELEMENTS_COUNT),
																  vertexBuffer(0),
																  indexBuffer(0),
																  texture(0),
																  effect(0),
																  renderBatchesCount(0) {
			renderBatches.resize(32);
			indexTransformBuffer.resize(32);
		}

		void Renderer::generateDefaultShaders() {
			/*
				Default polygon shader sources.

				TODO: move to somewhere else when the content can load effects
				and the effect class has been implemented.
			*/

			const char* const defaultPolygonVertexSource = 
											"#version 120\n"
											"attribute vec3 vertex_position;"
											"attribute vec4 vertex_color;"
											""
											"varying vec4 out_vertex_color;"
											"uniform mat4 transform;"
											""
											"void main() {"
											"	gl_Position = transform * vec4(vertex_position, 1.0);"
											"	out_vertex_color = vertex_color;"
											"}";

			const char* const defaultPolygonFragmentSource = 
											"#version 120\n"
											"varying vec4 out_vertex_color;"
											""
											"void main() {"
											"	gl_FragColor = out_vertex_color;"
											"}";

			const char* const defaultTexturedPolygonVertexSource = 
											"#version 120\n"
											"attribute vec3 vertex_position;"
											"attribute vec4 vertex_color;"
											"attribute in vec2 texture_coordinates;"
											""
											"varying vec2 out_texture_coordinates;"
											"varying vec4 out_vertex_color;"
											""
											"uniform mat4 transform;"
											""
											"void main() {"
											"	gl_Position = transform * vec4(vertex_position, 1.0);"
											"	out_texture_coordinates = texture_coordinates;"
											"	out_vertex_color = vertex_color;"
											"}";

			const char* const defaultTexturedPolygonFragmentSource = 
											"#version 120\n"
											"varying vec2 out_texture_coordinates;"
											"varying vec4 out_vertex_color;"
											""
											"uniform sampler2D sampler;"
											""
											"void main() {"
											"	gl_FragColor = texture2D(sampler, out_texture_coordinates) * out_vertex_color;"
											"}";

			uint32 vertex = 0;
			uint32 fragment = 0;
			uint32 defaultPolygonEffect = 0;
			uint32 defaultTexturedPolygonEffect = 0;

			// Create default polygon shader.
			graphicsDevice->compileShader(vertex, defaultPolygonVertexSource, ShaderType::Vertex);
			assert(!graphicsDevice->hasErrors());

			graphicsDevice->compileShader(fragment, defaultPolygonFragmentSource, ShaderType::Fragment);
			assert(!graphicsDevice->hasErrors());

			graphicsDevice->createProgram(defaultPolygonEffect);
			graphicsDevice->linkToProgram(defaultPolygonEffect, vertex, true);
			graphicsDevice->linkToProgram(defaultPolygonEffect, fragment, true);
			graphicsDevice->linkProgram(defaultPolygonEffect);
			assert(!graphicsDevice->hasErrors());

			vertex = fragment = 0;
			
			// Create default textured polygon shader.
			graphicsDevice->compileShader(vertex, defaultTexturedPolygonVertexSource, ShaderType::Vertex);
			assert(!graphicsDevice->hasErrors());

			graphicsDevice->compileShader(fragment, defaultTexturedPolygonFragmentSource, ShaderType::Fragment);
			assert(!graphicsDevice->hasErrors());

			graphicsDevice->createProgram(defaultTexturedPolygonEffect);
			graphicsDevice->linkToProgram(defaultTexturedPolygonEffect, vertex, true);
			graphicsDevice->linkToProgram(defaultTexturedPolygonEffect, fragment, true);
			graphicsDevice->linkProgram(defaultTexturedPolygonEffect);
			assert(!graphicsDevice->hasErrors());

			defaultEffects[static_cast<uint32>(RenderState::Waiting)]			= 0;
			defaultEffects[static_cast<uint32>(RenderState::Polygons)]			= defaultPolygonEffect;
			defaultEffects[static_cast<uint32>(RenderState::TexturedPolygons)]	= defaultTexturedPolygonEffect;
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

			if (nextOffset > 0) {
				vertices.offset(nextOffset);
			}
		}

		void Renderer::copyVertexData(const RenderElementData* const renderElementData, const RenderData* const renderData) {
			const uint32 elementVertexElementsCount		 = renderElementData->vertexElements;
			const uint32 vertexElementOffset			 = renderElementData->offset;

			const uint32 first							 = renderElementData->first;
			const uint32 last							 = renderElementData->last + 1;	// Add one to keep the index as zero-based.

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
			const uint32* indicesData					= reinterpret_cast<const uint32* const>(renderData->vertexIndices.data());

			const uint32 elementVertexElementsCount		= renderElementData->vertexElements;
			const uint32 bufferVertexElementsCount		= vertices.getElementsCount() / elementVertexElementsCount;
			const uint32 vertexOffset					= bufferVertexElementsCount - (renderElementData->last + 1 - renderElementData->first);

			if (indexTransformBuffer.size() < indicesCount) indexTransformBuffer.reserve(indexTransformBuffer.size() * 2);

			for (uint32 i = 0; i < indicesCount; i++) indexTransformBuffer[i] = indicesData[i] + vertexOffset;

			indices.push(indexTransformBuffer.data(), indicesCount);
		}

		void Renderer::flushRenderBatch(const RenderBatch* const renderBatch) {
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
				// TODO: not safe but works.
				RenderBatch& renderBatch = renderBatches[i];
				
				renderBatch.effect = renderBatch.effect <= 2 ? defaultEffects[renderBatch.effect] : renderBatch.effect;
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
			graphicsDevice->setShaderUniform(defaultEffects[1], "transform", (void*)&transform, UniformType::Mat4F);
			graphicsDevice->setShaderUniform(defaultEffects[2], "transform", (void*)&transform, UniformType::Mat4F);

			prepareRendering();
		}

		void Renderer::renderElement(const Renderable* const renderable) {
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
		void Renderer::renderElements(const Renderable* const renderables, const uint32 count) {
			for (uint32 i = 0; i < count; i++) renderElement(&renderables[i]);
		}

		void Renderer::endRendering() {
			renderBatchesCount = renderBatcher.getRenderBatchesCount();

			checkBatchEffects();
			updateBufferDatas();

			for (uint32 i = 0; i < renderBatchesCount; i++) flushRenderBatch(&renderBatches[i]);
		}

		Renderer::~Renderer() {
			for (uint32 i = 0; i < RENDER_STATES_COUNT; i++) delete renderSetups[i];
		}
	}
}