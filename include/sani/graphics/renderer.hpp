#pragma once

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/types.hpp"
#include <vector>

namespace sani {

	namespace graphics {

		class GraphicsDevice;

		typedef std::vector<VertexPositionColorTexture> PrimitiveComponentList;
		typedef std::vector<float32> VertexBuffer;
		typedef std::vector<uint32>	IndexBuffer;

		class Renderer {
		private:
			GraphicsDevice* graphicsDevice;
		public:
			/*
				Don't have a clear vision of how
				i want to use this low-level 
				renderer yet...
			*/

			Renderer(GraphicsDevice* graphicsDevice);

			bool initialize();

			void renderPrimitives(PrimitiveComponentList& components);

			void begin();
			void end();

			// void enableEffect(Effect* effect)
			// void disableEffects()

			// void beginTextRendering();
			//
			// void renderText(String& text, Vec2 position, Color color)
			// void setTextStyling(Styling styling)
			// void resetTextStyling()
			//
			// void endTextRendering();

			~Renderer();
		};
	}
}