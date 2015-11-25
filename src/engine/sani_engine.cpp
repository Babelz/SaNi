#include "sani/platform/time/engine_time.hpp"
#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {

		SaNiEngine::SaNiEngine() : running(false) {
		}

		bool SaNiEngine::initialize() {
			return false;
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

		void SaNiEngine::registerService(EngineService* const service) {
			return services.registerService(service);
		}
		void SaNiEngine::unregisterService(EngineService* const service) {
			return services.unregisterService(service);
		}

		void SaNiEngine::start() {
			// TODO: add services.
			running = true;

			if (!initialize()) return;

			EngineTime total(0.0, 0.0);

			while (running) {
				services.update(total);
			}
		}
		void SaNiEngine::quit() {
			// TODO: cleanup.
		}

		SaNiEngine::~SaNiEngine() {
		}
	}
}