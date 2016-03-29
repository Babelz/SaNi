#include "sani/graphics/default_shader_sources.hpp"
#include "sani/platform/graphics/graphics_enums.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/descriptions.hpp"
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
																   renderBatchesCount(0),
																   renderBatcher(defaultEffects, RenderStatesCount) {
			renderBatches.resize(InitialRenderBatchesCount);
			indexTransformBuffer.resize(InitialIndexTransformBufferSize);
		}

		void Renderer::generateDefaultShaders() {

			defaultEffects[static_cast<uint32>(RenderState::Waiting)]			= GraphicsEffect();
			defaultEffects[static_cast<uint32>(RenderState::Polygons)]			= GraphicsEffect::compile(graphicsDevice, DefaultPolygonVertexSource, DefaultPolygonFragmentSource);
			defaultEffects[static_cast<uint32>(RenderState::TexturedPolygons)]  = GraphicsEffect::compile(graphicsDevice, DefaultTexturedPolygonVertexSource, DefaultTexturedPolygonFragmentSource);
		}
		void Renderer::generateRenderSetups() {
			renderSetups[static_cast<uint32>(RenderState::Waiting)]				= nullptr;
			renderSetups[static_cast<uint32>(RenderState::Polygons)]			= new PolygonRenderSetup(graphicsDevice);
			renderSetups[static_cast<uint32>(RenderState::TexturedPolygons)]	= new TexturedPolygonRenderSetup(graphicsDevice);
		}
		void Renderer::generateBuffers() {
			BufferDescription vtxBuffDesc;
			vtxBuffDesc.type = BufferType::ArrayBuffer;
			vtxBuffDesc.usage = BufferUsage::Dynamic;
			vtxBuffDesc.bytes = vertices.getSize() * sizeof(float32);
			vtxBuffDesc.data = vertices.data();

			BufferDescription indexBuffDesc;
			indexBuffDesc.type = BufferType::ElementArrayBuffer;
			indexBuffDesc.usage = BufferUsage::Dynamic;
			indexBuffDesc.bytes = indices.getSize() * sizeof(uint32);
			indexBuffDesc.data = indices.data();

			vertexBuffer = graphicsDevice->createBuffer(&vtxBuffDesc);
			indexBuffer = graphicsDevice->createBuffer(&indexBuffDesc);
		}

		void Renderer::updateVertexBufferSize() {
			// Rebind buffer if it's size has changed.
			if (verticesSize != vertices.getSize()) {
				graphicsDevice->bindBuffer(BufferType::ArrayBuffer, vertexBuffer);
				graphicsDevice->setBufferData(BufferType::ArrayBuffer, vertices.data(), sizeof(float32) * vertices.getSize(), 0);
				graphicsDevice->bindBuffer(BufferType::ArrayBuffer, NULL);

				verticesSize = vertices.getSize();
			}
		}
		void Renderer::updateIndexBufferSize() {
			if (indicesSize != indices.getSize()) {
				graphicsDevice->bindBuffer(BufferType::ElementArrayBuffer, indexBuffer);
				graphicsDevice->setBufferData(BufferType::ElementArrayBuffer, indices.data(), indices.getSize() * sizeof(uint32), 0);
				graphicsDevice->bindBuffer(BufferType::ElementArrayBuffer, NULL);

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
			
			graphicsDevice->bindTexture(TextureTarget::Texture2D, renderBatch->texture);
			graphicsDevice->bindEffect(renderBatch->effect);

			if (vertexMode == VertexMode::NoIndexing)	graphicsDevice->drawArrays(renderMode, renderBatch->verticesBegin, renderBatch->verticesCount);
			else										graphicsDevice->drawElements(renderMode, PrimitiveType::UInt, renderBatch->indicesCount, renderBatch->indicesBegin);

			renderSetup->clear();

			graphicsDevice->bindTexture(TextureTarget::Texture2D, NULL);
			graphicsDevice->bindEffect(NULL);
		}

		void Renderer::checkBatchEffects() {
			for (uint32 i = 0; i < renderBatchesCount; i++) {
				RenderBatch& renderBatch = renderBatches[i];
				
				//renderBatch.effect = renderBatch.effect <= 2 ? defaultEffects[renderBatch.effect].getEffect() : renderBatch.effect;
			}
		}
		void Renderer::updateBufferDatas() {
			updateVertexBufferSize();
			updateIndexBufferSize();

			graphicsDevice->bindBuffer(BufferType::ArrayBuffer, vertexBuffer);
			graphicsDevice->setBufferData(BufferType::ArrayBuffer, vertices.data(), vertices.getElementsCount() * sizeof(float32), 0);
			graphicsDevice->bindBuffer(BufferType::ArrayBuffer, NULL);

			if (indices.getElementsCount() > 0) {
				graphicsDevice->bindBuffer(BufferType::ElementArrayBuffer, indexBuffer);
				graphicsDevice->setBufferData(BufferType::ElementArrayBuffer, indices.data(), indices.getElementsCount() * sizeof(uint32), 0);
				graphicsDevice->bindBuffer(BufferType::ElementArrayBuffer, NULL);
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

			return !graphicsDevice->hasErrors();
		}

		void Renderer::beginRendering(const math::Mat4f& transform) {
			// Set default effects transform uniform values.
			defaultEffects[static_cast<uint32>(RenderState::Polygons)].findUniform("transform")->setData((void*)&transform);
			defaultEffects[static_cast<uint32>(RenderState::TexturedPolygons)].findUniform("transform")->setData((void*)&transform);

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

			graphicsDevice->bindBuffer(BufferType::ArrayBuffer, vertexBuffer);
			graphicsDevice->bindBuffer(BufferType::ElementArrayBuffer, indexBuffer);

			for (uint32 i = 0; i < renderBatchesCount; i++) flushRenderBatch(&renderBatches[i]);
		
			graphicsDevice->bindBuffer(BufferType::ArrayBuffer, NULL);
			graphicsDevice->bindBuffer(BufferType::ElementArrayBuffer, NULL);
		}

		Renderer::~Renderer() {
			for (uint32 i = 0; i < RenderStatesCount; i++) delete renderSetups[i];
		}
	}
}