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

			// Transform state and state.
			math::Mat4f transform;
			RenderState renderState;
			VertexMode vertexMode;

			void generateRenderSetups();
			void generateBuffers();

			void updateVertexBufferSize();
			void updateIndexBufferSize();

			void swapRenderSetup();

			void prepareRendering(const RenderState renderState, const math::Mat4f& transform, const VertexMode vertexMode);
			void prepareRenderingPolygons(const RenderMode renderMode, const uint32 vertexElementsCount);
			void prepareRenderingPolygons(const RenderMode renderMode, const uint32 texture, const uint32 vertexElementsCount);

			void endRendering(const RenderState renderState);

			void presentPolygons();
			void presentIndexedPolygons();
		public:
			Renderer(GraphicsDevice& graphicsDevice);

			/// Returns the current render state.
			inline RenderState getRenderState() const;
			/// Returns the current vertex mode.
			inline VertexMode getVertexMode() const;
			/// Returns the current render mode.
			inline RenderMode getRenderMode() const;

			/// Returns the count of elements each vertex should have.
			inline uint32 getVertexElementsCount() const;

			bool initialize();

			/*
				TODO: add effect binding functions.
				TODO: create shader wrapper (effect class)
				TODO: create default shaders for this level of rendering (basic vtx and basic shader)
			*/

			/// Begins rendering polygons with given arguments.
			/// @param[in] transformation transformation
			/// @param[in] texture texture that will be used to texture the shapes
			/// @param[in] vertexElementsCount how many elements each vertex has
			/// @param[in] renderMode render mode
			void beginRenderingPolygons(const math::Mat4f& transform, const uint32 texture, const uint32 vertexElementsCount, const RenderMode renderMode);
			/// Begins rendering polygons with given arguments.
			/// @param[in] transformation transformation
			/// @param[in] vertexElementsCount how many elements each vertex has
			/// @param[in] renderMode render mode
			void beginRenderingPolygons(const math::Mat4f& transform, const uint32 vertexElementsCount, const RenderMode renderMode);

			/// Begins rendering polygons with given arguments.
			/// @param[in] transformation transformation
			/// @param[in] texture texture that will be used to texture the shapes
			/// @param[in] vertexElementsCount many many elements each vertex has
			/// @param[in] indices indices 
			/// @param[in] renderMode render mode
			void beginRenderingIndexedPolygons(const math::Mat4f& transform, const uint32 texture, const uint32 vertexElementsCount, const RenderMode renderMode);
			/// Begins rendering polygons with given arguments.
			/// @param[in] transformation transformation
			/// @param[in] vertexElementsCount how many elements each vertex has
			/// @param[in] indices indices
			/// @param[in] renderMode render mode
			void beginRenderingIndexedPolygons(const math::Mat4f& transform, const uint32 vertexElementsCount, const RenderMode renderMode);

			/// Renders given polygons.
			/// @param[in] vertices vertex elements
			/// @param[in] vertexElementsCount how many vertex elements to copy from vertices
			void renderPolygons(const float32* vertices, const uint32 vertexElementsCount);
			
			void renderIndexedPolygons(const float32* vertices, const uint32* indices, const uint32 verticesCount, const uint32 indicesCount, const uint32 indexObjects);
			
			/*
				TODO: add text functions.
				TODO: add index buffering.
			*/

			void endRendering();

			~Renderer();
		};
	}
}

#include "sani/graphics/inl/renderer.inl"