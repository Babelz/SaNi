#pragma once

#include "sani/forward_declare.hpp"
#include "sani/core/events.hpp"
#include "sani/types.hpp"
#include <list>

SANI_FORWARD_DECLARE_3(sani, engine, services, EngineService);
SANI_FORWARD_DECLARE_1(sani, EngineTime);

using namespace sani::engine::services;

namespace sani {

	namespace engine {

		/// @class ServiceRegistry service_registry.hpp "sani/engine/service_registry.hpp"
		/// @author voidbab
		///
		/// Service registry of the engine. Contains all services
		/// and is responsible of managing the services and 
		/// locating the for the consumers.
		class ServiceRegistry {
		private:
			std::list<EngineService*> services;

			EngineService* locate(std::function<bool(EngineService* const)> pred);

			bool contains(EngineService* const service);
		public:
			/// Triggered once a service has been registered.
			SANI_DECLARE_EVENT(registered,	void(EngineService* const));
			/// Triggered once a service has been unregistered.
			SANI_DECLARE_EVENT(unregistered, void(EngineService* const));

			ServiceRegistry();

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

			~ServiceRegistry();

			/*
				Deleted operators/methods.
			*/

			ServiceRegistry(const ServiceRegistry&) = delete;
			ServiceRegistry(const ServiceRegistry&&) = delete;

			void operator =(const ServiceRegistry&) = delete;
			void operator =(const ServiceRegistry&&) = delete;
		};
	}
}