#include "sani/engine/mono/graphics_device_mono.hpp"
#include "sani/engine/mono/mono_define.hpp"

#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"

#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/viewport.hpp"

#include "sani/engine/mono/mono_define.hpp"
#include "sani/engine/mono/structs_mono.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(graphicsdevice)

		using namespace sani::graphics;

		static GraphicsDevice* device;

		static MonoObject* GetViewport() {
			const Viewport& viewport = device->getViewport();

			return createViewport(viewport.x, viewport.y, viewport.width, viewport.height);
		}
		static void SetViewport(MonoViewport viewport) {
			device->setViewport(Viewport(viewport.x, viewport.y, viewport.w, viewport.h));
		}

		static void SetBackbufferSize(uint32 width, uint32 height) {
			device->setBackbufferSize(width, height);
		}
		static uint32 BackbufferWidth() {
			return device->getBackbufferWidth();
		}
		static uint32 BackbufferHeight() {
			return device->getBackbufferHeight();
		}

		static void SetSamplesCount(uint32 samples) {
			device->setSamplesCount(samples);
		}
		static int32 SamplesCount() {
			return device->getSamplesCount();
		}

		static void ApplyBackbufferChanges() {
			device->applyBackbufferChanges();
		}

		static bool IsFullscreen() {
			return device->isFullscreen();
		}

		static void Fullscreen() {
			device->fullscreen();
		}
		static void Windowed() {
			device->windowed();
		}

		static void getGraphicsDevice() {
			auto* getDevice = engine->createEmptyMessage<messages::DocumentMessage>();
			renderservice::getGraphicsDevice(getDevice);

			engine->routeMessage(getDevice);

			device = static_cast<GraphicsDevice*>(getDevice->getData());

			engine->releaseMessage(getDevice);
		}

		bool initialize() {
			getGraphicsDevice();

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, GetViewport, GetViewport);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, SetViewport, SetViewport);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, SetBackbufferSize, SetBackbufferSize);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, BackbufferWidth, BackbufferWidth);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, BackbufferHeight, BackbufferHeight);
			
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, SetSamplesCount, SetSamplesCount);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, SamplesCount, SamplesCount);
			
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, ApplyBackbufferChanges, ApplyBackbufferChanges);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, IsFullscreen, IsFullscreen);
			
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, Fullscreen, Fullscreen);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsDevice, Windowed, Windowed);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}