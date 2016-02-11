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

#include "sani/engine/services/file_system_service.hpp"
#include "sani/graphics/renderables/renderables.hpp"

#include "sani/engine/services/cvar_service.hpp"
#include "sani/core/cvar/cvar.hpp"
#include "sani/engine/services/contracts/cvar_service_contract.hpp"

#include "sani/graphics/layer.hpp"

namespace sani {

	namespace engine {

		// Win32 ctro impl.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
		SaNiEngine::SaNiEngine(const HINSTANCE hInstance) : services(ServiceRegistry()),		// Just to make clear that in what order we initialize stuff.
															channels(&services),
															hInstance(hInstance),
															sharedServiceMemory(BLOCK_1024KB, 1, DefragmentationPolicy::Automatic),
															running(false) {
#if 1 //_DEBUG
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

			// TODOF: notify cameras if device or window sizes change.
		}


		bool SaNiEngine::initializeFilesystem() {
			FileSystemService* fileSystemService = new FileSystemService(this);
			services.registerService(fileSystemService);
			fileSystemService->start();

			return !fileSystemService->hasErrors();
		}
		bool SaNiEngine::initializeCVarSystem() {
			CVarService* cvarService = new CVarService(this);
			services.registerService(cvarService);
			cvarService->start();

			return !cvarService->hasErrors();
		}
		bool SaNiEngine::initializeGraphics() {
			// Window init.
			graphics::Window* const window = new graphics::Window(hInstance, 1280, 720);

			if (!window->initialize()) return false;

			window->setTitle("SaNi Engine");
			window->show();

			// Device init.
			graphics::GraphicsDevice* const graphicsDevice = new graphics::GraphicsDevice(window->getHandle(),
																						  hInstance,
																						  1280,
																						  720);

			if (!graphicsDevice->initialize()) return false;

			window->sizeChanged += SANI_EVENT_HANDLER(void(), std::bind(&SaNiEngine::windowSizeChanged, graphicsDevice, window));

			if (!initializeRenderService(graphicsDevice, window)) return false;

			return true;
		}
		bool SaNiEngine::initializeRenderService(sani::graphics::GraphicsDevice* const graphicsDevice, graphics::Window* const window) {
			services::RenderService* renderService = new services::RenderService(this, graphicsDevice, window);
			services.registerService(renderService);
			renderService->start();

			return !renderService->hasErrors();
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

			/*
				TODO: add error messages.
			*/

			if (!initializeFilesystem())			return false;
			if (!initializeCVarSystem())			return false;
			if (!initializeGraphics())				return false;
			if (!initializeRenderableManagers())	return false;

#if 1 //_DEBUG
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
			if (!initialize()) return;

			running = true;

			sani::Time last = sani::Clock::now();
			sani::Time start = sani::Clock::now();

			// TODO: testing if the cvars get synced.
			auto* getCVars = createEmptyMessage<messages::DocumentMessage>();
			const uint32 command = static_cast<uint32>(2);

			getCVars->getRecipients().addRecipient("cvar service");
			getCVars->setCommand(command);

			routeMessage(getCVars);

			auto* vars = reinterpret_cast<std::vector<CVar* const>*>(getCVars->getData());
			
			CVar* const window_height = vars->operator[](0);
			CVar* const window_width = vars->operator[](1);
			
			window_width->write(800);
			window_height->write(600);

			while (running) {
				sani::Time current = sani::Clock::now();

				auto delta = current - last;
				auto total = current - start;
				
				last = current;

				EngineTime time(sani::toMilliseconds(sani::Time(total)),
								sani::toMilliseconds(sani::Time(delta)));

				// Update all services.
				services.update(time);

#if 1 //_DEBUG
				SANI_TRIGGER_EVENT(onUpdate, void(SaNiEngine* const, const EngineTime&), 
								   this, time);
#endif
			}

			services.terminate();
		}
		void SaNiEngine::quit() {
			running = false;
		}

		SaNiEngine::~SaNiEngine() {
		}
	}
}