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

#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/services/rectangle_manager.hpp"
#include "sani/engine/services/sprite_manager.hpp"
#include "sani/engine/services/circle_manager.hpp"
#include "sani/engine/services/triangle_manager.hpp"

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
#if _DEBUG
			SANI_INIT_EVENT(onInitialize, void(SaNiEngine* const engine));
			SANI_INIT_EVENT(onUpdate, void(SaNiEngine* const engine, const EngineTime&));
#endif
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

		bool SaNiEngine::initializeGraphics() {
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

			return true;
		}
		bool SaNiEngine::initializeRenderService() {
			services::RenderService* renderService = new services::RenderService(this, graphicsDevice);
			services.registerService(renderService);
			renderService->start();

			return true;
		}
		bool SaNiEngine::initializeRenderableManagers() {
			SpriteManager* spriteManager		= new services::SpriteManager(this);
			CircleManager* circleManager		= new services::CircleManager(this);
			TriangleManager* triangleManager	= new services::TriangleManager(this);
			RectangleManager* rectangleManager	= new services::RectangleManager(this);

			services.registerService(spriteManager);
			services.registerService(circleManager);
			services.registerService(triangleManager);
			services.registerService(rectangleManager);

			spriteManager->start();
			circleManager->start();
			triangleManager->start();
			rectangleManager->start();

			if (spriteManager->hasErrors())		return false;
			if (circleManager->hasErrors())		return false;
			if (triangleManager->hasErrors())	return false;
			if (rectangleManager->hasErrors())	return false;

			return true;
		}

		bool SaNiEngine::initialize() {
			// Create file system service
			// Create cvar service
			// Do platform initialization
			// Initialize rest of the services
			// Load game data
			// RUN!

			if (!initializeGraphics())				return false;
			if (!initializeRenderService())			return false;
			if (!initializeRenderableManagers())	return false;

			// Add default layer and camera.
			// TODO: remove once editor stuff is ready.
			auto createLayer = createEmptyMessage<messages::CommandMessage>();
			services::renderservice::createLayer(createLayer, "l1||1||0.0");

			auto createCamera = createEmptyMessage<messages::CommandMessage>();
			services::renderservice::createCamera(createCamera, "c1");

			auto getCameras = createEmptyMessage<messages::DocumentMessage>();
			services::renderservice::getCameras(getCameras);

			routeMessage(createLayer);
			routeMessage(createCamera);
			routeMessage(getCameras);

			std::vector<graphics::Camera2D* const>* cameras = static_cast<std::vector<graphics::Camera2D* const>*>(getCameras->getData());
			graphics::Camera2D* camera = *cameras->begin();
			deallocateShared(cameras);

			camera->setViewport(graphicsDevice->getViewport());
			camera->computeTransformation();

			releaseMessage(getCameras);

#if _DEBUG
			SANI_TRIGGER_EVENT(onInitialize, void(SaNiEngine* const), 
							   this);
#endif

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

				sani::Time current = sani::Clock::now();

				auto delta = current - last;
				auto total = current - start;
				
				last = current;

				EngineTime time(sani::toMilliseconds(sani::Time(total)),
								sani::toMilliseconds(sani::Time(delta)));

				// Update all services.
				services.update(time);

#if _DEBUG
				SANI_TRIGGER_EVENT(onUpdate, void(SaNiEngine* const, const EngineTime&), 
								   this, time);
#endif
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