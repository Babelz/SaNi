#include "sani/engine/mono/graphics_device_mono.hpp"
#include "sani/engine/mono/mono_define.hpp"

#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"

#include "sani/platform/graphics/graphics_device.hpp"

#include "sani/engine/mono/mono_define.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(graphicsdevice)



		bool initialize() {
			return true;
		}

		MONO_MODULE_IMPL_END
	}
}