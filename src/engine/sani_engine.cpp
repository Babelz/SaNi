#include "sani/engine/engine_service.hpp"
#include "sani/platform/time/engine_time.hpp"
#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {

		SaNiEngine::SaNiEngine() : running(false),
								   services(ServiceRegistry()),		// Just to make clear that in what order we initialize stuff.
								   channels(&services)	{
		}

		bool SaNiEngine::initialize() {
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
			channels::Channel* channel = channels.getChannel(message->type);

			channel->releaseMessage(message);
		}
		void SaNiEngine::routeMessage(messages::Message* const message) {
			channels::Channel* channel = channels.getChannel(message->type);

			channel->route(message);
		}

		void SaNiEngine::registerService(EngineService* const service) {
			return services.registerService(service);
		}
		void SaNiEngine::unregisterService(EngineService* const service) {
			return services.unregisterService(service);
		}

		void SaNiEngine::start() {
			// TODO: add services.
			if (!initialize()) return;
			
			running = true;

			sani::Time last = sani::Clock::now();
			sani::Time start = sani::Clock::now();
			
			while (running) {
				channels.route();

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