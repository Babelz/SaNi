#pragma once

#include "sani/graphics/render_batcher.hpp"
#include "sani/graphics/render_batch.hpp"
#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/graphics/vertex_mode.hpp"
#include "sani/core/math/matrix4.hpp"
#include "sani/forward_declare.hpp"
#include "sani/graphics/buffer.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, graphics, RenderSetup);
SANI_FORWARD_DECLARE_2(sani, graphics, Renderable);
SANI_FORWARD_DECLARE_2(sani, graphics, RenderElementData);
SANI_FORWARD_DECLARE_2(sani, graphics, RenderData);

namespace sani {

	namespace graphics {

		/*
			FIX: remove batching process from the renderer and 
			     move it to the render batcher.
		*/

		/// @class Renderer renderer.hpp "sani/graphics/renderer.hpp"
		/// @author voidbab
		///
		/// Low-level renderer of the rendering module. Uses
		/// render batches to join different elements into logical
		/// renderable batches that will be presented to the user.
		class Renderer {
		private:
			// Device and setup states.
			GraphicsDevice* const graphicsDevice;

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

			RenderBatcher renderBatcher;
			std::vector<RenderBatch> renderBatches;
			uint32 renderBatchesCount;
			
			uint32 elementCounter;
			uint32 elementsCount;

			// Used while transforming indices of 
			// render elements.
			std::vector<uint32> indexTransformBuffer;

			math::Mat4f transform;
			uint32 texture;
			uint32 effect;

			void generateDefaultShaders();
			void generateRenderSetups();
			void generateBuffers();

			void updateVertexBufferSize();
			void updateIndexBufferSize();

			void applyVertexOffset();

			void copyVertexData(const RenderElementData* const renderElementData, const RenderData* const renderData);
			void copyIndexData(const RenderElementData* const renderElementData, const RenderData* const renderData);

			void prepareFlushRenderBatch(const RenderBatch* renderBatch);
			void flushRenderBatch(const RenderBatch* const renderBatch);
			
			void checkBatchEffects();
			void updateBufferDatas();

			void prepareRendering();
		public:
			Renderer(GraphicsDevice* const graphicsDevice);

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
			
			// TODO: hazard! fucks up memory!
			//void renderElements(const Renderable* const renderables, const uint32 count);

			void endRendering();
			
			// TODO: should the renderer have a batcher? 
			//	     static layers need this, but i think
			//       that static layers could just be a collection
			//       of render targets (texture batches)
			//
			//void beginBatching();
			//void batchElement(const Renderable* const renderable);
			//void endBatching(std::vector<RenderBatch>& batches, Buffer<float32>& vertices);

			// TODO: impl post processing when render targets 
			//		 are working.
			//
			//void endRendering(Effect* const postProcessor);

			~Renderer();
		};
	}
}