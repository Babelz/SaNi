#pragma once

#include "sani/engine/service_registry.hpp"

namespace sani {

	namespace engine {
		
		/// @class SaNiEngine sani_engine.hpp "sani/engine/sani_engine.hpp"
		/// @author voidbab
		///
		/// The core of the engine. 
		class SaNiEngine {
		private:
			ServiceRegistry services;

			bool running;

			/// Initializes the engine.
			bool initialize();
		public:
			SaNiEngine();

			/// Returns the first service with given name and ID.
			EngineService* const locateService(const String& name, const uint32 id);
			/// Returns the first service with given name.
			EngineService* const locateService(const String& name);
			/// Returns the first service with given ID.
			EngineService* const locateService(const uint32 id);

			/// Registers new service.
			void registerService(EngineService* const service);
			/// Unregisters the given service and releases memory allocated by it.
			void unregisterService(EngineService* const service);

			/// Starts the engine.
			void start();
			/// Causes the engine to quit.
			void quit();

			~SaNiEngine();
		};
	}
}