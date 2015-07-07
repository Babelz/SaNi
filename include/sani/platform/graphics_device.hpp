#pragma once
#include "graphics_precompiled.hpp"

namespace sani {
	namespace graphics {
		
		/// @class Viewport graphics_device.hpp "sani/platform/graphics/graphics_device.hpp"
		/// @author voidbab
		/// 
		/// A virtual representation of the physical graphics adapter of this machine.
		class GraphicsDevice {
		private:
			class Impl;

			Impl* imp
		public:
			GraphicsDevice();

			/// Returns true if device has errors.
			inline bool hasErrors() const;
			/// Returns the next error if device has errors.
			GraphicsErrorType getError();

			/// Sets the viewport of the device.
			/// @param[in] viewport viewport to use
			void setViewport(const Viewport& viewport);
			/// Returns the current viewport to the user.
			Viewport& getViewport();

			/// Initializes the device.
			void initialize();
			/// Cleans the device.
			void cleanUp();
			/// Clears the device.
			void clear();

			~GraphicsDevice();
		};
	}
}

