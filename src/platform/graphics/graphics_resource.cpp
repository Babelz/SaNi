#include "sani/platform/graphics/graphics_resource.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace graphics {
		
		GraphicsResource::GraphicsResource(GraphicsDevice* const device) : id(0),
																		   device(device),
																		   disposeCalled(false),
																		   wasdDisposed(false) {
			SANI_ASSERT(device != nullptr);
		}

		GraphicsDevice* const GraphicsResource::getDevice() {
			return device;
		}
		void GraphicsResource::setID(const uint32 id) {
			this->id = id;
		}

		void GraphicsResource::dispose() {
			if (disposeCalled) return;

			wasdDisposed = onDispose();
		}

		bool GraphicsResource::disposed() const {
			return wasdDisposed;
		}

		uint32 GraphicsResource::getID() const {
			return id;
		}

		bool GraphicsResource::operator ==(const GraphicsResource& rhs) const {
			return this->id == rhs.id;
		}
		bool GraphicsResource::operator !=(const GraphicsResource& rhs) const {
			return !(*this == rhs);
		}
	}
}