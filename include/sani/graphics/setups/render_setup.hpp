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
		protected:
			GraphicsDevice* const getGraphicsDevice() const;
		public:
			RenderSetup(GraphicsDevice* const graphicsDevice);
			RenderSetup();
			
			/// Causes this setups render setups to be used.
			virtual void use() = 0;
			/// Clear all setups the render setup has initialized.
			virtual void clear() = 0;

			virtual ~RenderSetup();
		};
	}
}