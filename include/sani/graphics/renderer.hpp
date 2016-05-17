#pragma once

#include "sani/graphics/render_batcher.hpp"
#include "sani/graphics/render_batch.hpp"
#include "sani/platform/graphics/graphics_enums.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/graphics/vertex_mode.hpp"
#include "sani/core/math/matrix4.hpp"
#include "sani/forward_declare.hpp"
#include "sani/graphics/buffer.hpp"
#include "sani/graphics/graphics_effect.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, graphics, RenderSetup);
SANI_FORWARD_DECLARE_2(sani, graphics, Renderable);
SANI_FORWARD_DECLARE_2(sani, graphics, RenderElementData);
SANI_FORWARD_DECLARE_2(sani, graphics, RenderData);

namespace sani {

	namespace graphics {

		/// @class Renderer renderer.hpp "sani/graphics/renderer.hpp"
		/// @author voidbab
		///
		/// Low-level renderer of the rendering module. Uses
		/// render batches to join different elements into logical
		/// renderable batches that will be presented to the user.
		class Renderer {
		private:
			math::Mat4f transform;

			// Device and setup states.
			GraphicsDevice* const graphicsDevice;

			/*
				Effect and setup transition tables.
			*/

			// 0 null, 1 and 2 are valid.
			RenderSetup* renderSetups[RenderStatesCount];
			// 0 null, 1 and 2 are valid.
			GraphicsEffect defaultEffects[RenderStatesCount];

			// Device buffer names.
			uint32 vertexBuffer;
			uint32 indexBuffer;

			// Renderer buffers.
			Buffer<float32> vertices;
			uint32 verticesSize;

			Buffer<uint32> indices;
			uint32 indicesSize;

			RenderBatcher renderBatcher;
			uint32 renderBatchesCount;

			// Used while transforming indices of 
			// render elements.
			std::vector<uint32> indexTransformBuffer;
			
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
			
			void updateBufferDatas();

			void prepareRendering();
		public:
			Renderer(GraphicsDevice* const graphicsDevice);

			bool initialize();

			/// Begins rendering elements with given arguments.
			/// @param[in] transformation transformation
			void beginRendering(const math::Mat4f& transform);

			void renderElement(const Renderable* const renderable);
			
			void endRendering();
			
			~Renderer();
		};
	}
}