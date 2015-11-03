#pragma once

namespace sani {

	namespace graphics {

		class GraphicsDevice;

		/// @class RenderSetup render_setup.hpp "sani/graphics/render_setup.hpp"
		/// @author voidbab
		///
		/// Represents a self contained graphics setup.
		class RenderSetup {
		private:
			GraphicsDevice* const graphicsDevice;
		
			RenderMode renderMode;

			uint32 elements;
		protected:
			GraphicsDevice* const getGraphicsDevice() const;
		public:
			RenderSetup(GraphicsDevice* const graphicsDevice);
			RenderSetup();

			void setRenderMode(const RenderMode renderMode);
			RenderMode getRenderMode() const;

			void setElements(const uint32 elements);
			uint32 getElements() const;
			
			/// Causes this setups render setups to be used.
			virtual void use() = 0;
			/// Clear all setups the render setup has initialized.
			virtual void clear() = 0;

			virtual ~RenderSetup();
		};
	}
}