#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsEffect);
SANI_FORWARD_DECLARE_2(sani, graphics, RenderBatch);
SANI_FORWARD_DECLARE_2(sani, graphics, RenderElementData);

namespace sani {

	namespace graphics {

		/// @class RenderBatcher render_batcher.hpp "sani/graphics/render_batcher.hpp"
		/// @author voidbab
		///
		/// Class responsible of generating batches from given set of renderable elements.
		class RenderBatcher final {
		private:
			std::vector<RenderBatch> batches;
			// Iterator used to get the next batch.
			uint32 batchIterator;

			// Default effects given by the renderer.
			GraphicsEffect* const defaultEffects;
			const uint32 defaultEffectsCount;

			// How many batches we have created.
			uint32 renderBatchesCount;
			// Current batch pointer.
			RenderBatch* renderBatch;

			// Vertex and index elements count.
			uint32 vertexElements;
			uint32 indexElements;
			// Offset amount that should be applied to
			// vertex buffer.
			uint32 nextOffset;
			
			/// Computes next offset and applies it to the vertex elements.
			void updateOffset();
			
			/// Returns true if the given element should be batched alone.
			bool shouldBeBatchedAlone(const RenderElementData* renderElementData) const;
			
			/// Initializes current batch with the data contained
			/// in given element data.
			void initializeBatch(const RenderElementData* const renderElementData);
			/// Applies the given element data to current batch.
			void applyToBatch(const RenderElementData* const renderElementData);

			void swapBatch();

			RenderBatch* newBatch();
		public:
			RenderBatcher(GraphicsEffect* const defaultEffects, const uint32 count);
			
			/// Prepares the batcher for batching. Should
			/// always be called before batching.
			void prepareBatching();
			
			/// Returns count of batches.
			uint32 getRenderBatchesCount() const;
			/// Returns the next offset that should be applied.
			uint32 getNextOffset();

			const RenderBatch* const nextRenderBatch();
			
			/// Batches given element.
			void batchElement(const RenderElementData* const renderElementData, const uint32 elementCounter, const uint32 elementsCount);

			~RenderBatcher();
		};
	}
}