#include "sani/platform/base_graphics_device.hpp"

namespace sani {
	namespace graphics {

		BaseGraphicsDevice::BaseGraphicsDevice(const uint32 screenWidth, const int32 screenHeight) : viewport(0, 0, screenWidth, screenHeight) {
		}

		const Viewport& BaseGraphicsDevice::getViewport() const {
			return viewport;
		}
		void BaseGraphicsDevice::setViewport(const Viewport& viewport) {
			this->viewport = Viewport(viewport);
		}

		// Protected members.
		void BaseGraphicsDevice::pushError(const GraphicsErrorType error) {
			errors.push(error);
		}

		// Public members.
		bool BaseGraphicsDevice::initialize() {
			if (!platformInitialize()) {
				errors.push(GraphicsErrorType::InitializationError);

				return false;
			}

			return true;
		}

		bool BaseGraphicsDevice::hasErrors() const {
			return errors.size() > 0;
		}
		GraphicsErrorType BaseGraphicsDevice::getError() {
			if (errors.size() == 0) return GraphicsErrorType::NoError;

			const GraphicsErrorType next = errors.top();
			errors.pop();

			return next;
		}

		BaseGraphicsDevice::~BaseGraphicsDevice() {
		}
	}
}
