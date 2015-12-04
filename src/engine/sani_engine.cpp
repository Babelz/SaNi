#include "sani/engine/services/engine_service.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/engine/sani_engine.hpp"

#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/platform/graphics/window.hpp"

namespace sani {

	namespace engine {

		// Win32 ctro impl.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
		SaNiEngine::SaNiEngine(const HINSTANCE hInstance) : running(false),
															services(ServiceRegistry()),		// Just to make clear that in what order we initialize stuff.
															channels(&services),
															hInstance(hInstance) {
		}
#endif

		bool SaNiEngine::platformInitialize() {
			// TODO: read config from cvars.
			// TODO: add some error messages.
			// TODO: win32 impl only, add android init.

			// Init window.
			window = new graphics::Window(hInstance, 1280, 720);
			if (!window->initialize()) return false;

			window->sizeChanged += SANI_EVENT_HANDLER(void(), windowSizeChanged);
			window->closed += SANI_EVENT_HANDLER(void(), windowClosed);

			window->setTitle("SaNi Engine");
			window->show();

			graphicsDevice = new graphics::GraphicsDevice(window->getHandle(), 
														  hInstance, 
														  window->getWidth(), 
														  window->getHeight());

			if (!graphicsDevice->initialize()) return false;

			return true;
		}
		bool SaNiEngine::initializeServices() {
			return true;
		}

		void SaNiEngine::windowClosed() {
			quit();
		}
		void SaNiEngine::windowSizeChanged() {
			graphics::Viewport viewport;

			viewport.width = window->getClientWidth();
			viewport.height = window->getClientHeight();

			graphicsDevice->setViewport(viewport);

			graphicsDevice->setBackBufferWidth(viewport.width);
			graphicsDevice->setBackBufferHeight(viewport.height);

			// TODO: notify cameras that the views bounds have changed.
		}

		bool SaNiEngine::initialize() {
			// Create file system service
			// Create cvar service
			// Do platform initialization
			// Initialize rest of the services
			// Load game data
			// RUN!

			if (!platformInitialize()) return false;
			if (!initializeServices()) return false;

			// Create all initial services.
			return true;
		}

		EngineService* const SaNiEngine::locateService(const String& name, const uint32 id) {
			return services.locate(name, id);
		}
		EngineService* const SaNiEngine::locateService(const String& name) {
			return services.locate(name);
		}
		EngineService* const SaNiEngine::locateService(const uint32 id) {
			return services.locate(id);
		}

		messages::Message* const SaNiEngine::createEmptyMessage(MessageType const type) {
			channels::Channel* channel = channels.getChannel(type);

			return channel->createEmptyMessage();
		}
		void SaNiEngine::releaseMessage(messages::Message* const message) {
			channels::Channel* channel = channels.getChannel(message->type);

			channel->releaseMessage(message);
		}
		void SaNiEngine::routeMessage(messages::Message* const message) {
			channels::Channel* channel = channels.getChannel(message->type);

			channel->route(message);
		}

		void SaNiEngine::registerService(EngineService* const service) {
			return services.registerService(service);
		}
		void SaNiEngine::unregisterService(EngineService* const service) {
			return services.unregisterService(service);
		}

		void SaNiEngine::start() {
			// TODO: add services.
			if (!initialize()) return;
			
			running = true;

			sani::Time last = sani::Clock::now();
			sani::Time start = sani::Clock::now();
			
			while (running) {
				// Clear last frame and listen for window events.
				window->listen();

				// Do pre-update message routing.
				channels.route();

				sani::Time current = sani::Clock::now();

				auto delta = current - last;
				auto total = start - current;
				
				last = current;

				EngineTime time(static_cast<float64>(total.count()),
								static_cast<float64>(delta.count()));

				// Update all services.
				services.update(time);

				// Do post-update message routing.
				channels.route();
			}
		}
		void SaNiEngine::quit() {
			running = false;

			graphicsDevice->cleanUp();
			window->close();
		}

		SaNiEngine::~SaNiEngine() {
			delete graphicsDevice;
			delete window;
		}
	}
}