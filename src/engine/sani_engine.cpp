#include "sani/engine/services/engine_services.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {

		SaNiEngine::SaNiEngine() : running(false) {
		}

		bool SaNiEngine::initialize() {
			// Create all initial services.
			FileSystemService* fileSystemService = new FileSystemService(this);

			// Initialize/start all initial services.
			fileSystemService->start();

			// Register all initial services.
			services.registerService(fileSystemService);
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

			sani::Time last = sani::Clock::now();
			sani::Time start = sani::Clock::now();
			
			/*
				Possible update order
					1) entity
					2) component
					3) physics
					4) render data
					5) render?
			*/

			while (running) {
				sani::Time current = sani::Clock::now();

				auto delta = current - last;
				auto total = start - current;
				
				last = current;

				EngineTime time(static_cast<float64>(total.count()),
								static_cast<float64>(delta.count()));

				services.update(time);
			}
		}
		void SaNiEngine::quit() {
			// TODO: cleanup.
		}

		SaNiEngine::~SaNiEngine() {
		}
	}
}