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
			RenderSetup** renderSetups;
			RenderSetup* renderSetup;

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

			void generateRenderSetups();
			void generateBuffers();

			void updateVertexBufferSize();
			void updateIndexBufferSize();

			void swapRenderSetup(const RenderState renderState);
			void applyVertexOffset();

			void initializeBatch(const RenderElementData* const renderElementData);
			void swapBatch();
			
			void applyToBatch(const RenderElementData* const renderElementData);
			void batchElement(const RenderElementData* const renderElementData);
			void copyVertexData(const RenderElementData* const renderElementData, const RenderData* const renderData);
			void copyIndexData(const RenderElementData* const renderElementData, const RenderData* const renderData);

			void prepareFlushRenderBatch(const RenderBatch* renderBatch);
			void flushRenderBatch(const RenderBatch* const renderBatch);
			void updateBufferDatas();
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

			void render(const Renderable* const renderable);

			void endRendering();

			~Renderer();
		};
	}
}