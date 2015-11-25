#include "sani/engine/engine_service_provider.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/engine/engine_service.hpp"

#include <algorithm>

namespace sani {

	namespace engine {

		EngineServiceProvider::EngineServiceProvider() {
			SANI_INIT_EVENT(registered, void(EngineService* const));
			SANI_INIT_EVENT(unregistered, void(EngineService* const));
		}

		EngineService* EngineServiceProvider::locate(std::function<bool(EngineService* const)> pred) {
			auto it = std::find_if(services.begin(), services.end(), pred);

			EngineService* service = it != services.end() ? *it : nullptr;

			return service;
		}

		bool EngineServiceProvider::contains(EngineService* const service) {
			return std::find(services.begin(), services.end(), service) != services.end();
		}

		EngineService* const EngineServiceProvider::locate(const String& name, const uint32 id) {
			return locate([&name, &id](EngineService* const service) { return service->getName() == name && service->getID() == id; });
		}
		EngineService* const EngineServiceProvider::locate(const String& name) {
			return locate([&name](EngineService* const service) { return service->getName() == name; });
		}
		EngineService* const EngineServiceProvider::locate(const uint32 id) {
			return locate([&id](EngineService* const service) { return service->getID() == id; });
		}

		void EngineServiceProvider::registerService(EngineService* const service) {
			if (contains(service)) throw std::runtime_error("service already registered");
			
			services.push_back(service);

			SANI_TRIGGER_EVENT(registered, void(EngineService* const), service);
		}
		void EngineServiceProvider::unregisterService(EngineService* const service) {
			if (!contains(service)) return;

			services.remove(service);

			SANI_TRIGGER_EVENT(unregistered, void(EngineService* const), service);
		}

		void EngineServiceProvider::update(const EngineTime& time) {
			for (EngineService* const service : services) service->update(time);
		}

		EngineServiceProvider::~EngineServiceProvider() {
		}
	}
}