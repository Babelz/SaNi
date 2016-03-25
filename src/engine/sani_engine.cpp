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
#include "sani/engine/services/particle_emitter_manager.hpp"
#include "sani/engine/services/sprite_animation_manager.hpp"
#include "sani/engine/services/ecs/entity_manager.hpp"

#include "sani/engine/services/file_system_service.hpp"
#include "sani/graphics/renderables/renderables.hpp"

#include "sani/engine/services/cvar_service.hpp"
#include "sani/core/cvar/cvar.hpp"
#include "sani/engine/services/contracts/cvar_service_contract.hpp"

#include "sani/graphics/layer.hpp"

#include "sani/core/profiling/profiler.hpp"
#include "sani/platform/console.hpp"
#include "sani/engine/services/ecs/transform_manager.hpp"
#include "sani/core/logging/log_batcher.hpp"

#include <sstream>
#include <vector>

namespace sani {

	namespace engine {

		// Win32 ctro impl.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
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
			
			if (fileSystemService->start()) {
				FNCLOG_INF(log::OutFlags::All, "file system service started...");

				return true;
			}

			FNCLOG_ERR(log::OutFlags::All, "failed to start file system service!");

			return false;
		}
		bool SaNiEngine::initializeCVarSystem() {
			CVarService* cvarService = new CVarService(this);
			services.registerService(cvarService);
			
			if (cvarService->start()) {
				FNCLOG_INF(log::OutFlags::All, "cvar service started...");

				return true;
			}

			FNCLOG_ERR(log::OutFlags::All, "failed to start cvar service!");

			return false;
		}
		bool SaNiEngine::initializeGraphics() {
			// Window init.
			graphics::Window* const window = new graphics::Window(hInstance, 1280, 720);

			if (!window->initialize()) {
				FNCLOG_ERR(log::OutFlags::All, "could not create window");

				return false;
			}

			window->setTitle("SaNi Engine");
			window->show();

			// Device init.
			graphics::GraphicsDevice* const graphicsDevice = new graphics::GraphicsDevice(window->getHandle(),
																						  hInstance,
																						  1280,
																						  720);

			if (!graphicsDevice->initialize()) {
				FNCLOG_ERR(log::OutFlags::All, "graphics device initialization failed");

				return false;
			}

			window->sizeChanged += SANI_EVENT_HANDLER(void(), std::bind(&SaNiEngine::windowSizeChanged, graphicsDevice, window));

			if (!initializeRenderService(graphicsDevice, window)) return false;

			// All ok.
			return true;
		}
		bool SaNiEngine::initializeRenderService(sani::graphics::GraphicsDevice* const graphicsDevice, graphics::Window* const window) {
			services::RenderService* renderService = new services::RenderService(this, graphicsDevice, window);
			services.registerService(renderService);

			// All ok.
			if (renderService->start()) {
				FNCLOG_INF(log::OutFlags::All, "render service started...");
				
				return true;
			}

			FNCLOG_ERR(log::OutFlags::All, "failed to start render service");

			// Failed to init. Shit is hitting the fan.
			return false;
		}
		bool SaNiEngine::initializeRenderableManagers() {
			services::EngineService* services[] = {
				new services::SpriteManager(this),
				new services::CircleManager(this),
				new services::TriangleManager(this),
				new services::RectangleManager(this),
				new SpriteAnimationManager(this),
				new ParticleEmitterManager(this)
			};

			std::vector<String> errors;

			// Register.
			for (auto* service : services) registerService(service);

			// Start.
			for (auto* service : services) {
				if (!service->start()) {
					std::stringstream ss;
					ss << "failed to start renderable manager \"";
					ss << service->getName();
					ss << "\"";

					errors.push_back(ss.str());
				} else {
					std::stringstream ss;
					ss << "started renderable manager \"";
					ss << service->getName();
					ss << "\"";

					FNCLOG_INF(log::OutFlags::All, ss.str());
				}
			}

			// All ok.
			if (errors.empty()) {
				return true;
			}

			for (auto& str : errors) FNCLOG_ERR(log::OutFlags::All, str);

			// Shit is hitting the fan.
			return false;
		}
		bool SaNiEngine::initializeEntityComponentSystem() {
			EntityManager* entityManager = new EntityManager(this);
            services::EngineService* servicesToStart[] = {
                new services::TransformManager(this)
            };
            
			registerService(entityManager);
            for (auto* service : servicesToStart) registerService(service);

			// All ok.
			if (entityManager->start()) {
				FNCLOG_INF(log::OutFlags::All, "entity manager started...");
                for (auto* service : servicesToStart) {
                    if (service->start()) {
                        FNCLOG_INF(log::OutFlags::All, String8("Started service ") + service->getName());
                    }
                    else {
                        std::abort();
                    }
                    
                }
				return true;
			}

			FNCLOG_ERR(log::OutFlags::All, "failed to start entity manager!");

			// Shitting in the fan.
			return false;
		}

		bool SaNiEngine::initializeMono() {
			// TODO: initialize mono.
			return true;
		}

		bool SaNiEngine::loadUserServices() {
			// TODO: load user services from managed dll.
			return true;
		}
		bool SaNiEngine::loadScene() {
			// TODO: load the first scene.
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

			FNCLOG_INF(log::OutFlags::All, "engine init start...");

			if (!initializeFilesystem())			return false;
			if (!initializeCVarSystem())			return false;
			if (!initializeGraphics())				return false;
			if (!initializeRenderableManagers())	return false;
			if (!initializeEntityComponentSystem()) return false;

			FNCLOG_INF(log::OutFlags::All, "engine init ok!");

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
			if (!initialize()) {
				FNCLOG_ERR(log::OutFlags::All, "engine init failed, exiting...");

				return;
			}

			running = true;

			sani::Time last = sani::Clock::now();
			sani::Time start = sani::Clock::now();

			PROFILER_MAKE_ROOT;

			while (running) {
				START_PROFILER;

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
				
				STOP_PROFILER;
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