#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/setups/render_setups.hpp"
#include "sani/resource/texture2d.hpp"
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
			// Last vertex position.
			uint32 verticesEnd;

			// First vertex index position.
			uint32 indicesBegin;
			// Last vertex index position.
			uint32 indicesEnd;
			
			// Element this batch can be used to render.
			const RenderElementData* elementsData;

			// Statee elements.
			RenderState renderState;
			VertexMode vertexMode;
			RenderMode renderMode;

			// TODO: add these
			/*
				Effect* effect;
				Texture2D* texture;
			*/

			RenderBatch() : verticesBegin(0),
							verticesEnd(0),
							indicesBegin(0),
							indicesEnd(0),
							elementsData(nullptr) {
			}

			void resetBatch() {
				verticesBegin = 0;
				verticesEnd = 0;
				
				indicesBegin = 0;
				indicesEnd = 0;

				elementsData = nullptr;
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
															 renderSetup(nullptr),
															 vertexBuffer(0),
															 indexBuffer(0) {
			renderBatches.resize(32);
		}

		void Renderer::generateRenderSetups() {
			renderSetups = new RenderSetup*[RENDER_STATES_COUNT];
			
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
										 BufferUsage::Stream);


			graphicsDevice.setBufferData(BufferType::ElementArrayBuffer,
										 indices.getSize() * sizeof(uint32),
										 indices.data(),
										 BufferUsage::Stream);
		}

		void Renderer::updateVertexBufferSize() {
			// Rebind buffer if it's size has changed.
			if (verticesSize != vertices.getSize()) {
				graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

				graphicsDevice.setBufferData(BufferType::ArrayBuffer,
											 vertices.getSize() * sizeof(float32),
											 vertices.data(),
											 BufferUsage::Stream);

				verticesSize = vertices.getSize();
			}
		}
		void Renderer::updateIndexBufferSize() {
			if (indicesSize != indices.getSize()) {
				graphicsDevice.bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

				graphicsDevice.setBufferData(BufferType::ElementArrayBuffer,
											 indices.getSize() * sizeof(uint32),
											 indices.data(),
											 BufferUsage::Stream);

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
			const uint32 vertexElementsCount = renderBatch->elementsData->vertexElements;
			const uint32 vertexElementsModulo = vertices.getElementsCount() % vertexElementsCount;
			const uint32 vertexElementsOffset = vertexElementsCount - vertexElementsModulo;

			vertices.offset(vertexElementsOffset);
		}
		void Renderer::swapRenderSetup(const RenderState renderState) {
			const uint32 index = static_cast<uint32>(renderState);

			renderSetup = renderSetups[index];
		}

		void Renderer::initializeBatch(const RenderElementData* const renderElementData) {
			renderBatch->elementsData = renderElementData;

			/*
				TODO: add texturing.
			*/

			renderBatch->indicesBegin = indices.getElementsCount();
			renderBatch->indicesEnd = renderBatch->indicesBegin + renderElementData->indices;
			
			renderBatch->renderState = RenderState::Polygons;
			renderBatch->vertexMode = renderElementData->indices == 0 ? VertexMode::NoIndexing : VertexMode::Indexed;
			renderBatch->renderMode = renderElementData->renderMode;

			// Add possible vertex elements offset for this batch element.
			applyVertexOffset();	

			const uint32 vertexElementsCount = vertices.getElementsCount();
			const uint32 vertexOffset = vertexElementsCount > 0 ? 1 : 0;

			renderBatch->verticesBegin = vertexElementsCount / renderElementData->vertexElements;
			renderBatch->verticesEnd = renderBatch->verticesBegin;
		}
		void Renderer::swapBatch() {
			renderBatch = &renderBatches[renderBatchesCount];
			renderBatch->resetBatch();
			
			renderBatchesCount++;

			if (renderBatchesCount == renderBatches.size()) renderBatches.reserve(renderBatches.size() * 2);
		}

		void Renderer::applyToBatch(const RenderElementData* const renderElementData) {
			// Add one to keep the indexes as zero based.
			const uint32 verticesCount = (renderElementData->last + 1) - renderElementData->first;

			renderBatch->verticesEnd += verticesCount;
			renderBatch->indicesEnd += renderElementData->indices;
		}
		void Renderer::batchElement(const RenderElementData* const renderElementData) {
			if (renderBatch->elementsData == nullptr) {
				initializeBatch(renderElementData);
			}

			if (renderElementData->renderMode == RenderMode::TriangleFan || renderElementData->renderMode == RenderMode::LineLoop) {
				swapBatch();

				initializeBatch(renderElementData);
			} else if (renderElementData->groupIdentifier != renderBatch->elementsData->groupIdentifier) {
				// Check if we can batch this element to some recent batch.
				// If we can't just create new batch.
				//if (renderBatchesCount >= 1 && (renderBatchesCount < elementCounter)) {
				//	const uint32 batchesBegin = renderBatchesCount - elementCounter;
				//	
				//	uint32 i = batchesBegin;

				//	while (i < renderBatchesCount) {
				//		RenderBatch* const recentRenderBatch = &renderBatches[i];

				//		if (recentRenderBatch->elementsData->groupIdentifier == renderElementData->groupIdentifier) {
				//			RenderBatch* const temp = renderBatch;
				//			renderBatch = recentRenderBatch;

				//			applyToBatch(renderElementData);

				//			renderBatch = temp;

				//			return;
				//		}
				//	}
				//} else {
					// Can't batch to other batches, a new batch is required.
					swapBatch();

					initializeBatch(renderElementData);
				/*}*/
			}

			applyToBatch(renderElementData);
		}
		void Renderer::copyVertexData(const RenderElementData* const renderElementData, const RenderData* const renderData) {
			const uint32 elementVertexElementsCount = renderElementData->vertexElements;
			const uint32 vertexElementOffset = renderElementData->offset;

			const uint32 first = renderElementData->first;
			const uint32 last = renderElementData->last + 1;	// Add one to keep the index as zero-based.

			const uint32 firstVertexElement = first * (elementVertexElementsCount + vertexElementOffset);
			const uint32 lastVertexElement = last * (elementVertexElementsCount + vertexElementOffset);

			const uint32 vertexElementsCount = lastVertexElement - firstVertexElement;
			const uint32 verticesCount = last - first;
			
			const float32* const vertexElementsData = reinterpret_cast<const float32* const>(renderData->vertices.data());
			
			uint32 vertexElementPointer = firstVertexElement;
			
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
			if (renderSetup != nullptr) renderSetup->clear();

			const RenderState renderState = renderBatch->renderState;

			swapRenderSetup(renderState);
			renderSetup->setVertexElementsCount(renderBatch->elementsData->vertexElements);
			renderSetup->use();

			const VertexMode vertexMode = renderBatch->vertexMode;
			const RenderMode renderMode = renderBatch->renderMode;

			if (vertexMode == VertexMode::NoIndexing) {
				graphicsDevice.drawArrays(renderMode, renderBatch->verticesBegin, renderBatch->verticesEnd - renderBatch->verticesBegin);
			} else {
				const uint32 indicesCount = renderBatch->indicesEnd - renderBatch->indicesBegin;

				graphicsDevice.drawElements(renderMode, PrimitiveType::UInt, indicesCount, renderBatch->indicesBegin);
			}
		}
		void Renderer::updateBufferDatas() {
			updateVertexBufferSize();
			updateIndexBufferSize();

			graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

			graphicsDevice.setBufferSubData(BufferType::ArrayBuffer,
											0,
											vertices.getElementsCount() * sizeof(float32),
											vertices.data());

			graphicsDevice.bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

			graphicsDevice.setBufferSubData(BufferType::ElementArrayBuffer,
											0,
											indices.getElementsCount() * sizeof(uint32),
											indices.data());
		}

		bool Renderer::initialize() {
			generateRenderSetups();
			generateBuffers();

			return graphicsDevice.hasErrors();
		}

		void Renderer::beginRendering(const math::Mat4f& transform) {
			renderBatchesCount = 0;
			renderBatch = nullptr;
			
			vertices.resetBufferPointer();
			indices.resetBufferPointer();
			
			swapBatch();
		}

		void Renderer::render(const Renderable* const renderable) {
			elementsCount = renderable->renderData.renderElementsCount;

			for (elementCounter = 0; elementCounter < elementsCount; elementCounter++) {
				const uint32 renderElementIndex = renderable->renderData.renderElementIndices[elementCounter];
				const RenderElementData* const renderElementData = &renderable->renderData.renderElements[renderElementIndex];

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
			
			delete[] renderSetups;
		}
	}
}