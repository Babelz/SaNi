#pragma once

#include "sani/engine/messaging/channel_manager.hpp"
#include "sani/core/memory/heap_allocator.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/engine/service_registry.hpp"
#include "sani/forward_declare.hpp"
#include "sani/core/events.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include <Windows.h>

#endif

SANI_FORWARD_DECLARE_3(sani, engine, messages, Message);
SANI_FORWARD_DECLARE_3(sani, engine, channels, Channel);
SANI_FORWARD_DECLARE_2(sani, graphics, Window);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {

	namespace engine {
		
		/// @class SaNiEngine sani_engine.hpp "sani/engine/sani_engine.hpp"
		/// @author voidbab
		///
		/// The core of the engine. 
		class SaNiEngine {
		private:
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
			const HINSTANCE hInstance;
#endif

#if 1
			SANI_DECLARE_EVENT(onInitialize, void(SaNiEngine* const));
			SANI_DECLARE_EVENT(onUpdate, void(SaNiEngine* const, const EngineTime&));
#endif

			bool running;

			// Shared memory region used by the services to allocate
			// temporary stuff such as results for messages.
			HeapAllocator sharedServiceMemory;

			ServiceRegistry services;
			ChannelManager channels;

			static void windowSizeChanged(graphics::GraphicsDevice* const graphicsDevice, graphics::Window* const window);
			
			bool initializeFilesystem();
			bool initializeCVarSystem();
			bool initializeGraphics();
			bool initializeRenderService(graphics::GraphicsDevice* const graphicsDevice, graphics::Window* const window);
			bool initializeRenderableManagers();

			/// Initializes the engine.
			bool initialize();
		public:
			// Win32 ctor.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
			SaNiEngine(const HINSTANCE hInstance);
#endif

			/// Returns the first service with given name and ID.
			EngineService* const locateService(const String& name, const uint32 id);
			/// Returns the first service with given name.
			EngineService* const locateService(const String& name);
			/// Returns the first service with given ID.
			EngineService* const locateService(const uint32 id);

			messages::Message* const createEmptyMessage(MessageType const type);

			template <typename T>
			T* const createEmptyMessage();

			void releaseMessage(messages::Message* const message);
			void routeMessage(messages::Message* const message);

			/// Registers new service.
			void registerService(EngineService* const service);
			/// Unregisters the given service and releases memory allocated by it.
			void unregisterService(EngineService* const service);

			/// Starts the engine.
			void start();
			/// Causes the engine to quit.
			void quit();

			template<typename T>
			T* allocateShared();
			
			template<typename T>
			void deallocateShared(T* object);

			~SaNiEngine();
		};
	}
}

#include "sani/engine/impl/sani_engine.hpp"