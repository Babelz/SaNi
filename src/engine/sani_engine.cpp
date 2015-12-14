#include "sani/engine/services/engine_service.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/engine/sani_engine.hpp"

#include "sani/engine/services/render_service.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/platform/graphics/window.hpp"

#include "sani/core/memory/memory.hpp"

#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/peer_to_peer_message.hpp"
#include "sani/engine/services/contracts/render_service_contract.hpp"

#include "sani/graphics/renderables/renderables.hpp"

#include "sani/graphics/layer.hpp"

namespace sani {

	namespace engine {

		// Win32 ctro impl.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
		SaNiEngine::SaNiEngine(const HINSTANCE hInstance) : services(ServiceRegistry()),		// Just to make clear that in what order we initialize stuff.
															channels(&services),
															hInstance(hInstance),
															sharedServiceMemory(BLOCK_1024KB, 1, DefragmentationPolicy::Automatic) {
		}
#endif

		void SaNiEngine::windowSizeChanged(graphics::GraphicsDevice* const graphicsDevice, graphics::Window* const window) {
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

			// Window init.
			window = new graphics::Window(hInstance, 1280, 720);
			if (!window->initialize()) return false;

			window->setTitle("SaNi Engine");
			window->show();

			// Device init.
			graphicsDevice = new graphics::GraphicsDevice(window->getHandle(),
				hInstance,
				1280,
				720);

			if (!graphicsDevice->initialize()) return false;

			window->sizeChanged += SANI_EVENT_HANDLER(void(), std::bind(&SaNiEngine::windowSizeChanged, graphicsDevice, window));
			
			// Render service init.
			services::RenderService* renderService = new services::RenderService(this, graphicsDevice);
			services.registerService(renderService);
			renderService->start();

			auto createLayer = createEmptyMessage<messages::CommandMessage>();
			services::renderservice::createLayer(createLayer, "l1||1||0.0");

			auto createCamera = createEmptyMessage<messages::CommandMessage>();
			services::renderservice::createCamera(createCamera, "c1");

			auto getLayers = createEmptyMessage<messages::DocumentMessage>();
			services::renderservice::getLayers(getLayers);

			auto getCameras = createEmptyMessage<messages::DocumentMessage>();
			services::renderservice::getCameras(getCameras);

			routeMessage(createLayer);
			routeMessage(createCamera);
			routeMessage(getLayers);
			routeMessage(getCameras);

			std::vector<graphics::Layer* const>* layers = static_cast<std::vector<graphics::Layer* const>*>(getLayers->getData());
			graphics::Layer* layer = *layers->begin();
			deallocateShared(layers);

			graphics::Rectangle* rect = new graphics::Rectangle(100, 100, 128, 128);
			graphics::updateRenderData(*rect);
			graphics::recomputeBounds(*rect);
			layer->add(rect);

			std::vector<graphics::Camera2D* const>* cameras = static_cast<std::vector<graphics::Camera2D* const>*>(getCameras->getData());
			graphics::Camera2D* camera = *cameras->begin();
			deallocateShared(cameras);

			camera->setViewport(graphicsDevice->getViewport());
			camera->computeTransformation();

			releaseMessage(getCameras);
			releaseMessage(getLayers);

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
			channels::Channel* channel = channels.getChannel(message->getType());

			channel->releaseMessage(message);
		}
		void SaNiEngine::routeMessage(messages::Message* const message) {
			channels::Channel* channel = channels.getChannel(message->getType());

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

			sani::Time last = sani::Clock::now();
			sani::Time start = sani::Clock::now();
			
			while (window->isOpen()) {
				// Clear last frame and listen for window events.
				window->listen();

				graphicsDevice->clear(0.0f, 0.0f, 0.0f, 0.0f);

				sani::Time current = sani::Clock::now();

				auto delta = current - last;
				auto total = current - start;
				
				last = current;

				EngineTime time(static_cast<float64>(total.count()),
								static_cast<float64>(delta.count()));

				// Update all services.
				services.update(time);
			}

			graphicsDevice->cleanUp();
		}
		void SaNiEngine::quit() {
			window->close();
		}

		SaNiEngine::~SaNiEngine() {
			delete graphicsDevice;
			delete window;
		}
	}
}