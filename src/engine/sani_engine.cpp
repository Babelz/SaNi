#include "sani/engine/services/engine_service.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/engine/sani_engine.hpp"

#include "sani/engine/services/render_service.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/platform/graphics/window.hpp"

#include "sani/engine/services/contracts/cvar_service_contract.hpp"
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
#include "sani/engine/services/text_manager.hpp"
#include "sani/engine/services/ecs/entity_manager.hpp"

#include "sani/engine/services/file_system_service.hpp"
#include "sani/graphics/renderables/renderables.hpp"

#include "sani/engine/services/cvar_service.hpp"
#include "sani/core/cvar/cvar.hpp"
#include "sani/engine/mono/mono_runtime.hpp"

#include "sani/graphics/layer.hpp"

#include "sani/core/profiling/profiler.hpp"
#include "sani/platform/console.hpp"
#include "sani/core/logging/log.hpp"

#include "sani/core/logging/log_batcher.hpp"
#include "sani/engine/services/resource_manager_handler_service.hpp"

#include "sani/engine/mono/mono_runtime.hpp"
#include "sani/engine/mono/mono_define.hpp"
#include "sani/engine/mono//texture2d_mono.hpp"
#include "sani/engine/mono/services_mono.hpp"
#include "sani/engine/mono/rectangle_mono.hpp"
#include "sani/engine/mono/resource_manager_mono.hpp"
#include "sani/engine/mono/layers_mono.hpp"
#include "sani/engine/mono/layer_mono.hpp"

#include <sstream>
#include <vector>

namespace sani {

	namespace engine {

		// Win32 ctro impl.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
		SaNiEngine::SaNiEngine(const HINSTANCE hInstance) : services(ServiceRegistry()),		// Just to make clear that in what order we initialize stuff.
															channels(&services),
															hInstance(hInstance),
															sharedServiceMemory(Block1024Kb, 1, DefragmentationPolicy::Automatic),
															running(false) {
			SANI_INIT_EVENT(onInitialize, void(SaNiEngine* const engine));
			SANI_INIT_EVENT(onUpdate, void(SaNiEngine* const engine, const EngineTime&));
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
		bool SaNiEngine::initializeResourceManagerHandler() {
			ResourceManagerHandlerService* resourceManagerHandler = new ResourceManagerHandlerService(this);
			services.registerService(resourceManagerHandler);

			if (resourceManagerHandler->start()) {
				FNCLOG_INF(log::OutFlags::All, "resource manager handler service started...");

				return true;
			}

			FNCLOG_ERR(log::OutFlags::All, "failed to start resource manager handler service!");

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
			// Get cvars.
			auto* message = createEmptyMessage<messages::DocumentMessage>();
			cvarservice::listCVars(message);
			routeMessage(message);

			auto cvars = static_cast<std::vector<CVar* const>*>(message->getData());

			// Read values.
			int32 windowWidth = 0;
			int32 windowHeight = 0;
			int32 backbufferWidth = 0;
			int32 backbufferHeight = 0;
			int32 samplesCount = 0;

			FIND_VAR_OR_DEFAULT(cvars, "window_width", windowWidth, 1280);
			FIND_VAR_OR_DEFAULT(cvars, "window_height", windowHeight, 720);
			FIND_VAR_OR_DEFAULT(cvars, "backbuffer_width", backbufferWidth, windowWidth);
			FIND_VAR_OR_DEFAULT(cvars, "backbuffer_height", backbufferHeight, windowHeight);
			FIND_VAR_OR_DEFAULT(cvars, "samples_count", samplesCount, 8);

			SANI_ASSERT(windowWidth > 0 && windowHeight > 0);
			SANI_ASSERT(backbufferWidth > 0 && backbufferHeight > 0);
			SANI_ASSERT(samplesCount > 0);

			// Cleanup.
			releaseMessage(message);
			deallocateShared(cvars);

			// Window init.
			graphics::Window* const window = new graphics::Window(hInstance, static_cast<uint32>(windowWidth), static_cast<uint32>(windowHeight));

			if (!window->initialize()) {
				FNCLOG_ERR(log::OutFlags::All, "could not create window");

				return false;
			}

			window->setTitle("SaNi Engine");
			window->show();

			// Device init.
			graphics::GraphicsDevice* const graphicsDevice = new graphics::GraphicsDevice(window->getHandle(), hInstance);
			graphicsDevice->initialize(static_cast<uint32>(backbufferWidth), static_cast<uint32>(backbufferHeight), static_cast<uint32>(samplesCount));

			if (graphicsDevice->hasErrors()) {
				FNCLOG_ERR(log::OutFlags::All, "graphics device initialization failed");

				while (graphicsDevice->hasErrors()) {
					const auto deviceError = graphicsDevice->nextError();

					std::stringstream ss;
					ss << "DEV ERR: ";
					ss << deviceError.getMessage();

					FNCLOG_ERR(log::OutFlags::All, ss.str());
				}
				
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
				new services::SpriteAnimationManager(this),
				new services::ParticleEmitterManager(this),
				new services::TextManager(this)
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

			services.registerService(entityManager);

			// All ok.
			if (entityManager->start()) {
				FNCLOG_INF(log::OutFlags::All, "entity manager started...");

				return true;
			}

			FNCLOG_ERR(log::OutFlags::All, "failed to start entity manager!");

			// Shitting in the fan.
			return false;
		}

		bool SaNiEngine::initializeMono() {
			auto* message = createEmptyMessage<messages::DocumentMessage>();
			cvarservice::listCVars(message);
			routeMessage(message);

			auto cvars = static_cast<std::vector<CVar* const>*>(message->getData());

			String monoAssembliesPath;
			String monoLibrariesPath;
			String monoConfigPath;
			String monoAssemblyName;
			String monoDependencies;

			FIND_VAR_OR_DEFAULT(cvars, "mono_assemblies_path", monoAssembliesPath, "");
			FIND_VAR_OR_DEFAULT(cvars, "mono_libraries_path", monoLibrariesPath, "");
			FIND_VAR_OR_DEFAULT(cvars, "mono_config_path", monoConfigPath, "");
			FIND_VAR_OR_DEFAULT(cvars, "mono_assembly_name", monoAssemblyName, "");
			FIND_VAR_OR_DEFAULT(cvars, "mono_dependencies", monoDependencies, "");

			releaseMessage(message);
			deallocateShared(cvars);
			
			if (mono::MonoRuntime::instance().start(monoAssembliesPath, monoLibrariesPath, monoConfigPath, monoAssemblyName, monoDependencies)) {
				FNCLOG_INF(log::OutFlags::All, "mono runtime started...");
			} else {
				FNCLOG_ERR(log::OutFlags::All, "failed to start mono runtime!");

				return false;
			}

			MONO_REGISTER_MODULE(texture2d);
			MONO_REGISTER_MODULE(resourcemanager);
			MONO_REGISTER_MODULE(rectangle);
			MONO_REGISTER_MODULE(layer);
			MONO_REGISTER_MODULE(layers);
			MONO_REGISTER_MODULE(services);

			FNCLOG_INF(log::OutFlags::All, "loaded all mono modules...");

			return true;
		}

		bool SaNiEngine::initialize() {
			// Create file system service
			// Create cvar service
			// Do platform initialization
			// Initialize rest of the services
			// Load game data
			// RUN!

			FNCLOG_INF(log::OutFlags::All, "engine init start...");

			if (!initializeFilesystem())				return false;
			if (!initializeCVarSystem())				return false;
			if (!initializeGraphics())					return false;
			if (!initializeResourceManagerHandler())	return false;
			if (!initializeRenderableManagers())		return false;
			if (!initializeEntityComponentSystem())		return false;
			if (!initializeMono())						return false;

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
			mono::MonoRuntime::instance().shutdown();
		}
	}
}