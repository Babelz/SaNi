#pragma once


#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/types.hpp"
#include <vector>

namespace sani {

	namespace graphics {

		class GraphicsDevice;

		/// @class Renderer renderer.hpp "sani/graphics/renderer.hpp"
		/// @author voidbab
		///
		/// Low-level renderer of the rendering module. Uses different states
		/// to determine what will be rendered.
		class Renderer {
		private:
			GraphicsDevice* graphicsDevice;

			RenderState renderState;
		public:
			Renderer(GraphicsDevice* graphicsDevice);

			void beginRendering(const RenderState state);
			void endRendering(const RenderState state);

			// void renderUserPrimitives(const UserPrimitives& primitives);
			// void renderPrimitives(const Primitive& primitive);
			// void renderText()
			// void renderRichText()

			~Renderer();
		};
	}
}