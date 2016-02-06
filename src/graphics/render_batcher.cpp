#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/render_element_data.hpp"
#include "sani/graphics/render_batcher.hpp"
#include "sani/graphics/render_batch.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/graphics/graphics_effect.hpp"

namespace sani {

	namespace graphics {

		RenderBatcher::RenderBatcher(GraphicsEffect* const defaultEffects, const uint32 defaultEffectsCount)
			: renderBatches(nullptr), renderBatch(nullptr), renderBatchesCount(0), vertexElements(0), indexElements(0),
			  nextOffset(0), defaultEffects(defaultEffects), defaultEffectsCount(defaultEffectsCount) {
		}

		void RenderBatcher::updateOffset() {
			// No need to add offset.
			if (renderBatchesCount <= 1) return;

			const RenderBatch* const last = &renderBatches->operator[](renderBatchesCount - 2);

			// No need to add offset, same vertex elements count.
			if (last->elementsData->vertexElements == renderBatch->elementsData->vertexElements) return;

			// From less elements to more.
			// Offset = vtxElemes - vetxElemsMod.
			const uint32 vertexElementsCount	= renderBatch->elementsData->vertexElements;
			const uint32 vertexElementsModulo	= vertexElements % vertexElementsCount;
			const uint32 vertexElementsOffset	= (vertexElementsCount - vertexElementsModulo);

			nextOffset = vertexElementsOffset;
			vertexElements += nextOffset;
		}

		bool RenderBatcher::shouldBeBatchedAlone(const RenderElementData* renderElementData) const {
			const RenderMode renderMode = renderElementData->renderMode;

			return renderMode == RenderMode::TriangleFan || renderMode == RenderMode::LineLoop || renderMode == RenderMode::Lines;
		}
		
		void RenderBatcher::initializeBatch(const RenderElementData* const renderElementData) {
			renderBatch->elementsData = renderElementData;

			renderBatch->indicesBegin = indexElements * sizeof(uint32);

			const RenderState renderState	= renderElementData->texture == 0 ? RenderState::Polygons : RenderState::TexturedPolygons;
			renderBatch->vertexMode			= renderElementData->indices ==	0 ? VertexMode::NoIndexing : VertexMode::Indexed;
			renderBatch->renderMode			= renderElementData->renderMode;

			renderBatch->texture			= renderElementData->texture;
			renderBatch->effect				= renderElementData->effect == nullptr ? defaultEffects[static_cast<uint32>(renderState)].getEffect() : renderElementData->effect->getEffect();
			renderBatch->renderSetup		= static_cast<uint32>(renderState);

			// Check for possible vertex elements offset for this batch element.
			updateOffset();

			renderBatch->verticesBegin = vertexElements / renderElementData->vertexElements;
		}
		void RenderBatcher::applyToBatch(const RenderElementData* const renderElementData) {
			// Add one to keep the indexes as zero based.
			const uint32 verticesCount = (renderElementData->last + 1) - renderElementData->first;

			renderBatch->verticesCount	+= verticesCount;
			renderBatch->indicesCount	+= renderElementData->indices;

			vertexElements	+= (renderElementData->last + 1 - renderElementData->first) * renderElementData->vertexElements;
			indexElements	+= renderElementData->indices;
		}

		void RenderBatcher::swapBatch() {
			renderBatch = &renderBatches->operator[](renderBatchesCount);
			renderBatch->resetBatch();

			renderBatchesCount++;

			if (renderBatchesCount == renderBatches->size()) renderBatches->resize(renderBatches->size() * 2);
		}

		void RenderBatcher::prepareBatching(std::vector<RenderBatch>* const renderBatches) {
			this->renderBatches = renderBatches;
			
			renderBatchesCount = 0;
			vertexElements = 0;
			indexElements = 0;
			nextOffset = 0;
			
			swapBatch();
		}

		uint32 RenderBatcher::getRenderBatchesCount() const {
			return renderBatchesCount;
		}
		uint32 RenderBatcher::getNextOffset() {
			uint32 offset = nextOffset;
			nextOffset = 0;

			return offset;
		}
		
		void RenderBatcher::batchElement(const RenderElementData* const renderElementData, const uint32 elementCounter, const uint32 elementsCount) {
			if (renderBatch->elementsData == nullptr) {
				initializeBatch(renderElementData);
			} else if (shouldBeBatchedAlone(renderElementData)) {
				swapBatch();

				initializeBatch(renderElementData);
			} else if (renderElementData->groupIdentifier != renderBatch->elementsData->groupIdentifier) {
				// Check if we can batch this element to some recent batch.
				// If we can't just create new batch.
				if (renderBatchesCount >= 1 && (elementCounter < renderBatchesCount)) {
					const uint32 batchesBegin = renderBatchesCount - (elementCounter + 1);

					uint32 i = batchesBegin;

					while (i < renderBatchesCount) {
						RenderBatch* const recentRenderBatch = &renderBatches->operator[](i);

						if (recentRenderBatch->elementsData->groupIdentifier == renderElementData->groupIdentifier) {
							RenderBatch* const temp = renderBatch;
							renderBatch = recentRenderBatch;

							applyToBatch(renderElementData);

							renderBatch = temp;

							return;
						}

						i++;
					}
				}

				// Can't batch to other batches, a new batch is required.
				swapBatch();

				initializeBatch(renderElementData);
			}

			applyToBatch(renderElementData);
		}

		RenderBatcher::~RenderBatcher() {
		}
	}
}