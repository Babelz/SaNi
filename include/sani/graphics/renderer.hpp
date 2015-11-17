#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/graphics/vertex_mode.hpp"
#include "sani/core/math/matrix4.hpp"
#include "sani/graphics/buffer.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {
		
		class GraphicsDevice;
		class RenderSetup;
		class Renderable;
		class RenderBatch;
		class RenderElementData;
		class RenderData;

		/// @class Renderer renderer.hpp "sani/graphics/renderer.hpp"
		/// @author voidbab
		///
		/// Low-level renderer of the rendering module. Uses different states
		/// to determine what will be rendered.
		class Renderer {
		private:
			// Device and setup states.
			GraphicsDevice& graphicsDevice;

			/*
				Effect and setup transition tables.
			*/

			// 0 null, 1 and 2 are valid.
			RenderSetup* renderSetups[RENDER_STATES_COUNT];
			// 0 null, 1 and 2 are valid.
			uint32 defaultEffects[RENDER_STATES_COUNT];

			// API buffers.
			uint32 vertexBuffer;
			uint32 indexBuffer;

			// Renderer buffers.
			Buffer<float32> vertices;
			uint32 verticesSize;

			Buffer<uint32> indices;
			uint32 indicesSize;

			std::vector<RenderBatch> renderBatches;
			uint32 renderBatchesCount;
			RenderBatch* renderBatch;
			
			uint32 elementCounter;
			uint32 elementsCount;

			math::Mat4f transform;
			uint32 texture;
			uint32 effect;

			void generateDefaultShaders();
			void generateRenderSetups();
			void generateBuffers();

			void updateVertexBufferSize();
			void updateIndexBufferSize();

			void applyVertexOffset();

			void initializeBatch(const RenderElementData* const renderElementData);
			void swapBatch();

			const bool shouldBeBatchedAlone(const RenderElementData* renderElementData) const;

			void applyToBatch(const RenderElementData* const renderElementData);
			void batchElement(const RenderElementData* const renderElementData);
			void copyVertexData(const RenderElementData* const renderElementData, const RenderData* const renderData);
			void copyIndexData(const RenderElementData* const renderElementData, const RenderData* const renderData);

			void prepareFlushRenderBatch(const RenderBatch* renderBatch);
			void flushRenderBatch(const RenderBatch* const renderBatch);
			void updateBufferDatas();

			void prepareRendering();
		public:
			Renderer(GraphicsDevice& graphicsDevice);

			bool initialize();

			/*
				TODO: add effect binding functions.
				TODO: create shader wrapper (effect class)
				TODO: create default shaders for this level of rendering (basic vtx and basic shader)
			*/

			/// Begins rendering elements with given arguments.
			/// @param[in] transformation transformation
			void beginRendering(const math::Mat4f& transform);
			void renderElement(const Renderable* const renderable);
			void endRendering();
			
			// TODO: should the renderer have a batcher? 
			//	     static layers need this, but i think
			//       that static layers could just be a collection
			//       of render targets (texture batches)
			//
			//void beginBatching();
			//void batchElement(const Renderable* const renderable);
			//void endBatching(std::vector<RenderBatch>& batches, Buffer<float32>& vertices);

			~Renderer();
		};
	}
}