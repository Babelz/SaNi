#pragma once

#include "sani/forward_declare.hpp"
#include "sani/core/events.hpp"
#include "sani/types.hpp"
#include <list>

SANI_FORWARD_DECLARE_2(sani, engine, EngineService);
SANI_FORWARD_DECLARE_1(sani, EngineTime);

namespace sani {

	namespace engine {

		/// @class EngineServiceProvider engine_service_provider.hpp "sani/engine/engine_service_provider.hpp"
		/// @author voidbab
		///
		/// Service provider of the engine. Contains all services
		/// and is responsible of managing the services.
		class EngineServiceProvider {
		private:
			std::list<EngineService*> services;

			EngineService* locate(std::function<bool(EngineService* const)> pred);

			bool contains(EngineService* const service);
		public:
			/// Triggered once a service has been registered.
			SANI_DECLARE_EVENT(registered,	void(EngineService* const));
			/// Triggered once a service has been unregistered.
			SANI_DECLARE_EVENT(unregistered, void(EngineService* const));

			EngineServiceProvider();

			/// Returns the first service with given name and ID.
			EngineService* const locate(const String& name, const uint32 id);
			/// Returns the first service with given name.
			EngineService* const locate(const String& name);
			/// Returns the first service with given ID.
			EngineService* const locate(const uint32 id);

			/// Registers new service.
			void registerService(EngineService* const service);
			/// Unregisters the given service and releases memory allocated by it.
			void unregisterService(EngineService* const service);

			/// Updates all services.
			void update(const EngineTime& time);
			
			bool hasErrors() const;

			~EngineServiceProvider();

			/*
				Deleted operators/methods.
			*/

			EngineServiceProvider(const EngineServiceProvider&) = delete;
			EngineServiceProvider(const EngineServiceProvider&&) = delete;

			void operator =(const EngineServiceProvider&) = delete;
			void operator =(const EngineServiceProvider&&) = delete;
		};
	}
}