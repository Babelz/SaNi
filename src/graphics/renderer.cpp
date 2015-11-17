#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/setups/render_setups.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		#define INITIAL_BUFFER_ELEMENTS_COUNT 32768

		/*
			RenderBatch class
		
			Represents a part of the rendering process.
			Can contain one or more elements that will be
			rendered.
		*/
		class RenderBatch {
		public:
			// First vertex position.
			uint32 verticesBegin;
			uint32 verticesCount;

			// First vertex index position.
			uint32 indicesBegin;
			uint32 indicesCount;
			
			uint32 texture;
			uint32 effect;

			// Element this batch can be used to render.
			const RenderElementData* elementsData;
			RenderSetup* renderSetup;

			// State elements.
			VertexMode vertexMode;
			RenderMode renderMode;

			// TODO: add these
			/*
				Effect* effect;
			*/

			RenderBatch() : verticesBegin(0),
							verticesCount(0),
							indicesBegin(0),
							indicesCount(0),
							elementsData(nullptr),
							renderSetup(nullptr),
							texture(0) {
			}

			void resetBatch() {
				verticesBegin = 0;
				verticesCount = 0;
				
				indicesBegin = 0;
				indicesCount = 0;

				texture = 0;

				elementsData = nullptr;
				renderSetup = nullptr;
			}

			~RenderBatch() {
			}
		};
		
		// For starters, reserve 128kb worth of vertex memory (32768 float32 elements).
		// Keep the buffer usage as dynamic (memory as the limit).

		Renderer::Renderer(GraphicsDevice& graphicsDevice) : graphicsDevice(graphicsDevice),
															 vertices(INITIAL_BUFFER_ELEMENTS_COUNT, BufferSizing::Dynamic),
															 indices(INITIAL_BUFFER_ELEMENTS_COUNT, BufferSizing::Dynamic),
															 verticesSize(INITIAL_BUFFER_ELEMENTS_COUNT),
															 indicesSize(INITIAL_BUFFER_ELEMENTS_COUNT),
															 renderBatch(nullptr),
															 renderBatchesCount(0),
															 vertexBuffer(0),
															 indexBuffer(0),
															 texture(0),
															 effect(0) {
			renderBatches.resize(32);
		}

		void Renderer::generateDefaultShaders() {
			/*
				Default polygon shader sources.

				TODO: move to somewhere else when the content can load effects
				and the effect class has been implemented.
			*/

			const char* const defaultPolygonVertexSource = 
											"#version 330 core\n"
											"layout(location = 0) in vec3 vertex_position;"
											"layout(location = 1) in vec4 color;"
											""
											"out vec4 out_color;"
											"uniform mat4 transform;"
											""
											"void main() {"
											""
											""
											"	gl_Position = transform * vec4(vertex_position, 1.0);"
											"	out_color = color;"
											""
											"}";

			const char* const defaultPolygonFragmentSource = 
											"#version 330 core\n"
											"in vec4 out_color;"
											"out vec4 vertex_color;"
											""
											"void main(){"
											""
											"	vertex_color = out_color;"
											""
											"}";

			uint32 polygonVertex = 0;
			uint32 polygonFragment = 0;
			uint32 defaultPolygonEffect = 0;

			graphicsDevice.compileShader(polygonVertex, defaultPolygonVertexSource, ShaderType::Vertex);
			assert(!graphicsDevice.hasErrors());

			graphicsDevice.compileShader(polygonFragment, defaultPolygonFragmentSource, ShaderType::Fragment);
			assert(!graphicsDevice.hasErrors());

			graphicsDevice.createProgram(defaultPolygonEffect);
			graphicsDevice.linkToProgram(defaultPolygonEffect, polygonVertex, true);
			graphicsDevice.linkToProgram(defaultPolygonEffect, polygonFragment, true);
			graphicsDevice.linkProgram(defaultPolygonEffect);
			assert(!graphicsDevice.hasErrors());

			defaultEffects[static_cast<uint32>(RenderState::Waiting)]			= 0;
			defaultEffects[static_cast<uint32>(RenderState::Polygons)]			= defaultPolygonEffect;
			defaultEffects[static_cast<uint32>(RenderState::TexturedPolygons)]	= 0;
		}
		void Renderer::generateRenderSetups() {
			renderSetups[static_cast<uint32>(RenderState::Waiting)]				= nullptr;
			renderSetups[static_cast<uint32>(RenderState::Polygons)]			= new PolygonRenderSetup(&graphicsDevice);
			renderSetups[static_cast<uint32>(RenderState::TexturedPolygons)]	= new TexturedPolygonRenderSetup(&graphicsDevice);
		}
		void Renderer::generateBuffers() {
			graphicsDevice.generateBuffer(vertexBuffer);
			graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

			graphicsDevice.generateBuffer(indexBuffer);
			graphicsDevice.bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

			graphicsDevice.setBufferData(BufferType::ArrayBuffer,
										 vertices.getSize() * sizeof(float32),
										 vertices.data(),
										 BufferUsage::Dynamic);


			graphicsDevice.setBufferData(BufferType::ElementArrayBuffer,
										 indices.getSize() * sizeof(uint32),
										 indices.data(),
										 BufferUsage::Dynamic);
		}

		void Renderer::updateVertexBufferSize() {
			// Rebind buffer if it's size has changed.
			if (verticesSize != vertices.getSize()) {
				graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

				graphicsDevice.setBufferData(BufferType::ArrayBuffer,
											 vertices.getSize() * sizeof(float32),
											 vertices.data(),
											 BufferUsage::Dynamic);

				verticesSize = vertices.getSize();
			}
		}
		void Renderer::updateIndexBufferSize() {
			if (indicesSize != indices.getSize()) {
				graphicsDevice.bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

				graphicsDevice.setBufferData(BufferType::ElementArrayBuffer,
											 indices.getSize() * sizeof(uint32),
											 indices.data(),
											 BufferUsage::Dynamic);

				indicesSize = indices.getSize();
			}
		}

		void Renderer::applyVertexOffset() {
			// No need to add offset.
			if (renderBatchesCount <= 1) return;

			const RenderBatch* last = &renderBatches[renderBatchesCount - 1];

			// No need to add offset, same vertex elements count.
			if (last->elementsData->vertexElements == renderBatch->elementsData->vertexElements) return;

			// From less elements to more.
			// Offset = vtxElemes - vetxElemsMod.
			const uint32 vertexElementsCount	= renderBatch->elementsData->vertexElements;
			const uint32 vertexElementsModulo	= vertices.getElementsCount() % vertexElementsCount;
			const uint32 vertexElementsOffset	= vertexElementsCount - vertexElementsModulo;

			vertices.offset(vertexElementsOffset);
		}

		void Renderer::initializeBatch(const RenderElementData* const renderElementData) {
			renderBatch->elementsData = renderElementData;

			/*
				TODO: add texturing.
			*/

			renderBatch->indicesBegin		 = indices.getElementsCount();
			
			const RenderState renderState	 = renderElementData->texture == 0 ? RenderState::Polygons : RenderState::TexturedPolygons;
			renderBatch->vertexMode			 = renderElementData->indices == 0 ? VertexMode::NoIndexing : VertexMode::Indexed;
			renderBatch->renderMode			 = renderElementData->renderMode;

			renderBatch->texture			 = renderElementData->texture;
			renderBatch->effect				 = renderElementData->effect == 0 ? defaultEffects[static_cast<uint32>(renderState)] : renderElementData->effect;
			renderBatch->renderSetup		 = renderSetups[static_cast<uint32>(renderState)];

			// Add possible vertex elements offset for this batch element.
			applyVertexOffset();	

			renderBatch->verticesBegin		 = vertices.getElementsCount() / renderElementData->vertexElements;
		}
		void Renderer::swapBatch() {
			renderBatch = &renderBatches[renderBatchesCount];
			renderBatch->resetBatch();
			
			renderBatchesCount++;

			if (renderBatchesCount == renderBatches.size()) renderBatches.reserve(renderBatches.size() * 2);
		}

		const bool Renderer::shouldBeBatchedAlone(const RenderElementData* renderElementData) const {
			const RenderMode renderMode = renderElementData->renderMode;

			return renderMode == RenderMode::TriangleFan || renderMode == RenderMode::LineLoop || renderMode == RenderMode::Lines;
		}

		void Renderer::applyToBatch(const RenderElementData* const renderElementData) {
			// Add one to keep the indexes as zero based.
			const uint32 verticesCount = (renderElementData->last + 1) - renderElementData->first;

			renderBatch->verticesCount += verticesCount;
			renderBatch->indicesCount += renderElementData->indices;
		}
		void Renderer::batchElement(const RenderElementData* const renderElementData) {
			if (renderBatch->elementsData == nullptr) {
				initializeBatch(renderElementData);
			}

			if (shouldBeBatchedAlone(renderElementData)) {
				swapBatch();

				initializeBatch(renderElementData);
			} else if (renderElementData->groupIdentifier != renderBatch->elementsData->groupIdentifier) {
				// Check if we can batch this element to some recent batch.
				// If we can't just create new batch.
				if (renderBatchesCount >= 1 && (renderBatchesCount < elementCounter)) {
					const uint32 batchesBegin = renderBatchesCount - elementCounter;
					
					uint32 i = batchesBegin;

					while (i < renderBatchesCount) {
						RenderBatch* const recentRenderBatch = &renderBatches[i];

						if (recentRenderBatch->elementsData->groupIdentifier == renderElementData->groupIdentifier) {
							RenderBatch* const temp = renderBatch;
							renderBatch = recentRenderBatch;

							applyToBatch(renderElementData);

							renderBatch = temp;

							return;
						}
					}
				} else {
					// Can't batch to other batches, a new batch is required.
					swapBatch();

					initializeBatch(renderElementData);
				}
			}

			applyToBatch(renderElementData);
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
			const uint32 indicesCount = renderElementData->indices;
			const uint32* indicesData = reinterpret_cast<const uint32* const>(renderData->vertexIndices.data());

			indices.push(indicesData, indicesCount);
		}

		void Renderer::flushRenderBatch(const RenderBatch* const renderBatch) {
			const VertexMode vertexMode = renderBatch->vertexMode;
			const RenderMode renderMode = renderBatch->renderMode;

			RenderSetup* const renderSetup = renderBatch->renderSetup;
			renderSetup->setVertexElementsCount(renderBatch->elementsData->vertexElements);
			renderSetup->use();

			graphicsDevice.bindTexture(renderBatch->texture);
			graphicsDevice.useProgram(renderBatch->effect);

			if (vertexMode == VertexMode::NoIndexing) {
				graphicsDevice.drawArrays(renderMode, renderBatch->verticesBegin, renderBatch->verticesCount);
			} else {
				graphicsDevice.drawElements(renderMode, PrimitiveType::UInt, renderBatch->indicesCount, renderBatch->indicesBegin);
			}

			renderSetup->clear();

			graphicsDevice.bindTexture(0);
			graphicsDevice.useProgram(0);
		}
		void Renderer::updateBufferDatas() {
			updateVertexBufferSize();
			updateIndexBufferSize();

			graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

			graphicsDevice.setBufferSubData(BufferType::ArrayBuffer,
											0,
											vertices.getElementsCount() * sizeof(float32),
											vertices.data());

			if (indices.getElementsCount() > 0) {
				graphicsDevice.bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

				graphicsDevice.setBufferSubData(BufferType::ElementArrayBuffer,
												0,
												indices.getElementsCount() * sizeof(uint32),
												indices.data());
			}
		}

		void Renderer::prepareRendering() {
			renderBatchesCount = 0;
			renderBatch = nullptr;

			vertices.resetBufferPointer();
			indices.resetBufferPointer();

			swapBatch();
		}

		bool Renderer::initialize() {
			generateDefaultShaders();
			generateRenderSetups();
			generateBuffers();

			return graphicsDevice.hasErrors();
		}

		void Renderer::beginRendering(const math::Mat4f& transform) {
			graphicsDevice.setShaderUniform(defaultEffects[1], "transform", (void*)&transform, UniformType::Mat4F);
			
			/*
				TODO: set texture effect transform.
			*/

			prepareRendering();
		}

		void Renderer::renderElement(const Renderable* const renderable) {
			elementsCount = renderable->renderData.renderElementsCount;

			for (elementCounter = 0; elementCounter < elementsCount; elementCounter++) {
				const uint32 renderElementIndex						= renderable->renderData.renderElementIndices[elementCounter];
				const RenderElementData* const renderElementData	= &renderable->renderData.renderElements[renderElementIndex];

				batchElement(renderElementData);

				copyVertexData(renderElementData, &renderable->renderData);
				copyIndexData(renderElementData, &renderable->renderData);
			}
		}

		void Renderer::endRendering() {
			updateBufferDatas();

			for (uint32 i = 0; i < renderBatchesCount; i++) flushRenderBatch(&renderBatches[i]);
		}

		Renderer::~Renderer() {
			for (uint32 i = 0; i < RENDER_STATES_COUNT; i++) delete renderSetups[i];
		}
	}
}