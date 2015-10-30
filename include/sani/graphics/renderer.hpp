#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/core/math/matrix4.hpp"
#include "sani/graphics/buffer.hpp"
#include "sani/types.hpp"

#include <vector>

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
			uint32 vertexArray;
			uint32 vertexBuffer;

			// Renderer buffers.
			Buffer<float32> vertices;
			uint32 verticesSize;

			// Transform state and state.
			math::Mat4f transform;
			RenderState state;

			void generateRenderSetups();
			void generateBuffers();

			void swapRenderSetup();
			
			void beginRendering(const RenderState state, const math::Mat4f& transform);
			void endRendering(const RenderState state);
			
			void presentUserPrimitives();
		public:
			Renderer(GraphicsDevice& graphicsDevice);

			bool initialize();

			void beginRenderingUserPrimitives(const math::Mat4f& transform, const uint32 vertices, const RenderMode renderMode);
			void renderUserPrimitives(Buffer<float32>& vertices);

			//void beginRenderingPredefinedPrimitives(const math::Mat4f& transform);
			//void beginRenderingTextures(const math::Mat4f& transform);
			//void beginRenderingText(const math::Mat4f& transform);
			//void beginRenderingRichText(const math::Mat4f& transform);

			void endRendering();

			~Renderer();
		};
	}
}