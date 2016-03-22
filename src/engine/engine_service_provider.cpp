#include "sani/platform/time/engine_time.hpp"
#include "sani/engine/service_registry.hpp"
#include "sani/engine/services/engine_service.hpp"

#include <algorithm>

namespace sani {

	namespace engine {

		ServiceRegistry::ServiceRegistry() {
			SANI_INIT_EVENT(registered, void(EngineService* const));
			SANI_INIT_EVENT(unregistered, void(EngineService* const));
		}

		EngineService* ServiceRegistry::locate(std::function<bool(EngineService* const)> pred) {
			auto it = std::find_if(services.begin(), services.end(), pred);

			return it != services.end() ? *it : nullptr;
		}

		bool ServiceRegistry::contains(EngineService* const service) {
			return std::find(services.begin(), services.end(), service) != services.end();
		}

		EngineService* const ServiceRegistry::locate(const String& name, const uint32 id) {
			return locate([&name, &id](EngineService* const service) { return service->getName() == name && service->getID() == id; });
		}
		EngineService* const ServiceRegistry::locate(const String& name) {
			return locate([&name](EngineService* const service) { return service->getName() == name; });
		}
		EngineService* const ServiceRegistry::locate(const uint32 id) {
			return locate([&id](EngineService* const service) { return service->getID() == id; });
		}

		void ServiceRegistry::registerService(EngineService* const service) {
			if (contains(service)) return;

			services.push_back(service);

			SANI_TRIGGER_EVENT(registered, void(EngineService* const), service);
		}
		void ServiceRegistry::unregisterService(EngineService* const service) {
			if (!contains(service)) return;

			services.remove(service);

			SANI_TRIGGER_EVENT(unregistered, void(EngineService* const), service);

			delete service;
		}

		void ServiceRegistry::update(const EngineTime& time) {
			for (EngineService* const service : services) {
				if(service->getState() == ServiceState::Running) service->update(time);
			}
		}

		bool ServiceRegistry::hasErrors() const {
			for (EngineService* const service : services) if (service->hasErrors()) return true;

			return false;
		}

		void ServiceRegistry::terminate() {
			for (EngineService* const service : services) service->terminate();
		}

		ServiceRegistry::~ServiceRegistry() {
			for (EngineService* const service : services) delete service;
		}
	}
}