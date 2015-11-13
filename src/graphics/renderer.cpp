#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/setups/render_setups.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		#define INITIAL_BUFFER_ELEMENTS_COUNT 32768
		
		/*
			Render batch class
		*/

		class RenderBatch {
		public:
			uint32 verticesBegin;
			uint32 verticesEnd;

			uint32 indicesBegin;
			uint32 indicesEnd;
			uint32 indicesCount;

			const RenderElementData* elementsData;
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
															 renderBatches(32, BufferSizing::Dynamic),
															 verticesSize(INITIAL_BUFFER_ELEMENTS_COUNT),
															 indicesSize(INITIAL_BUFFER_ELEMENTS_COUNT),
															 renderBatch(nullptr),
															 renderSetup(nullptr),
															 vertexBuffer(0),
															 indexBuffer(0) {
		}

		void Renderer::generateRenderSetups() {
			renderSetups = new RenderSetup*[RENDER_STATES_COUNT];
			
			renderSetups[static_cast<uint32>(RenderState::Waiting)]				= nullptr;
			renderSetups[static_cast<uint32>(RenderState::Polygons)]			= new PolygonRenderSetup(&graphicsDevice);
			renderSetups[static_cast<uint32>(RenderState::TexturedPolygons)]	= new TexturedPolygonRenderSetup(&graphicsDevice);
			renderSetups[static_cast<uint32>(RenderState::Text)]				= new TexturedPolygonRenderSetup(&graphicsDevice);
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

		void Renderer::swapRenderSetup(const RenderState renderState) {
			const uint32 index = static_cast<uint32>(renderState);

			renderSetup = renderSetups[index];
		}
		void Renderer::swapBatch() {
			renderBatches.push(RenderBatch());

			renderBatch = &renderBatches.data()[renderBatches.getElementsCount() - 1];
		}

		void Renderer::batchElement(const RenderElementData* const renderElementData) {
			if (renderBatch->elementsData == nullptr) {
				renderBatch->elementsData = renderElementData;

				renderBatch->verticesBegin = vertices.getElementsCount();
				renderBatch->indicesBegin = indices.getElementsCount();

				renderBatch->indicesCount = renderElementData->indices;
				
				renderBatch->renderState = RenderState::Polygons;
				renderBatch->vertexMode = VertexMode::NoIndexing;
				renderBatch->renderMode = renderElementData->renderMode;
			}

			if (renderElementData->groupIdentifier != renderBatch->elementsData->groupIdentifier) {
				//if (renderBatches.getElementsCount() > 1) {
				//	RenderBatch* const batchers = renderBatches.data();
				//	RenderBatch* const last = &batchers[renderBatches.getElementsCount() - 2];

				//	if (last->elementsData->groupIdentifier == renderElementData->groupIdentifier) {
				//		RenderBatch* const current = renderBatch;
				//		renderBatch = last;

				//		batchElement(renderElementData);

				//		renderBatch = current;

				//		return;
				//	}
				//}

				swapBatch();

				batchElement(renderElementData);

				return;
			}

			const uint32 verticesCount = renderElementData->last- renderElementData->first;

			// Add one to keep the vertices index zero-based.
			renderBatch->verticesEnd += verticesCount + 1;
			renderBatch->indicesEnd += renderElementData->indices;
		}
		void Renderer::copyVertexData(const RenderElementData* const renderElementData, const RenderData* const renderData) {
			const uint32 vertexElements = renderElementData->vertexElements;
			const uint32 vertexElementOffset = renderElementData->offset;

			const uint32 first = renderElementData->first;
			const uint32 last = renderElementData->last + 1;	// Add one to keep the index as zero-based.

			const uint32 firstVertexElement = first * (vertexElements + vertexElementOffset);
			const uint32 lastVertexElement = last * (vertexElements + vertexElementOffset);
			const uint32 vertexElementsCount = lastVertexElement - firstVertexElement;
			const uint32 verticesCount = last - first;

			const float32* const vertexData = reinterpret_cast<const float32* const>(renderData->vertices.data());

			if (vertexElementOffset != 0) {
				uint32 vertexPointer = firstVertexElement;

				for (uint32 i = 0; i < verticesCount; i++) {
					vertices.push(&vertexData[vertexPointer], vertexElements);
					
					vertexPointer += vertexElements + vertexElementOffset;
				}
			} else {
				vertices.push(&vertexData[firstVertexElement], vertexElementsCount);
			}
		}
		void Renderer::copyIndexData(const RenderElementData* const renderElementData, const RenderData* const renderData) {
			//const uint32 indicesCount = renderElementData->indices;
			//const uint32* indicesData = reinterpret_cast<const uint32* const>(renderData->vertexIndices.data());

			//indices.push(indicesData, indicesCount);
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
				graphicsDevice.drawArrays(renderMode, renderBatch->verticesBegin, renderBatch->verticesEnd);
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
			vertices.resetBufferPointer();
			indices.resetBufferPointer();
			renderBatches.resetBufferPointer();

			renderBatches.push(RenderBatch());

			renderBatch = &renderBatches.data()[renderBatches.getElementsCount() - 1];
			renderBatch->resetBatch();
		}

		void Renderer::render(const Renderable* const renderable) {
			// First render call.
			elementsCount = renderable->renderData.renderElementsCount;

			for (elementCounter = 0; elementCounter < elementsCount; elementCounter++) {
				const uint32 elementIndex = renderable->renderData.renderElementIndices[elementCounter];
				const RenderElementData* const renderElementData = &renderable->renderData.renderElements[elementIndex];

				batchElement(renderElementData);

				copyVertexData(renderElementData, &renderable->renderData);
				copyIndexData(renderElementData, &renderable->renderData);
			}
		}

		void Renderer::endRendering() {
			updateBufferDatas();

			const RenderBatch* const renderBatchesData = renderBatches.data();

			for (uint32 i = 0; i < renderBatches.getElementsCount(); i++) {
				const RenderBatch* const renderBatch = &renderBatchesData[i];
				
				flushRenderBatch(renderBatch);
			}

			renderBatch = nullptr;
		}

		Renderer::~Renderer() {
			for (uint32 i = 0; i < RENDER_STATES_COUNT; i++) delete renderSetups[i];
			
			delete[] renderSetups;
		}
	}
}