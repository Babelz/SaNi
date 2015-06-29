#pragma once

#include "sani/platform/graphics_precompiled.hpp"
#include <stack>

class Window;

namespace sani {
	namespace graphics {

		/// @class BaseGraphicsDevice base_graphics_device.hpp "sani/platform/graphics/base_graphics_device.hpp"
		/// @author voidbab
		///
		/// "Virtual" representation of the physical graphics adapter. Common interface used to
		/// wrap different graphics APIs.
		class BaseGraphicsDevice {
		private:
			std::stack<GraphicsErrorType> errors;	// Device errors. Can be translated to API errors.
			Viewport viewport;						// Default viewport.
		protected:
			virtual bool platformInitialize() const = 0;

			void pushError(const GraphicsErrorType error);
		public:
			BaseGraphicsDevice(const uint32 screenWidth, const int32 screenHeight);

			const Viewport& getViewport() const;
			void setViewport(const Viewport& viewport);

			virtual const Window& getWindow() const = 0;

			/// Initialize the device.
			/// @returns true if device was initialized successfully and no errors occurred.
			bool initialize();

			/// Checks if the graphics device contains errors.
			/// @returns true if the device has encountered errors
			bool hasErrors() const;
			/// Returns next error.
			/// @returns GraphicsErrorType::NoError if there aren't any errors.
			GraphicsErrorType getError();
			
			virtual ~BaseGraphicsDevice();
		};
	}
}

