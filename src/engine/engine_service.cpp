#include "sani/engine/engine_service.hpp"

namespace sani {

	namespace engine {

		uint32 EngineService::idGenerator = 0;

		EngineService::EngineService(const String& name, SaNiEngine* const engine) : name(name),
																					 id(idGenerator++),
																					 engine(engine),
																					 state(ServiceState::Uninitialized) {
		}
		
		bool EngineService::onInitialize() {
			return true;
		}
		void EngineService::onUpdate(const EngineTime& time) {
		}

		void EngineService::onSuspend() {
		}
		bool EngineService::onResume() {
			return true;
		}
		void EngineService::onStop() {
		}

		SaNiEngine* const EngineService::getEngine() {
			return engine;
		}

		void EngineService::pushError(const String& error) {
			errors.push(error);
		}

		ServiceState EngineService::getState() const {
			return state;
		}
		const String& EngineService::getName() const {
			return name;
		}
		const uint32 EngineService::getID() const {
			return id;
		}

		void EngineService::suspend() {
			switch (state) {
			case sani::engine::ServiceState::Uninitialized:
			case sani::engine::ServiceState::Suspended:
			case sani::engine::ServiceState::Stopped:
			default:
				throw std::runtime_error("invalid operation at this time");
			case sani::engine::ServiceState::Running:
				onSuspend();
				break;
			}

			state = ServiceState::Suspended;
		}
		bool EngineService::start() {
			bool results = false;
			
			switch (state) {
			case sani::engine::ServiceState::Uninitialized:
				results = onInitialize();
				break;
			case sani::engine::ServiceState::Suspended:
				results = onResume();
				break;
			case sani::engine::ServiceState::Stopped:
			case sani::engine::ServiceState::Running:
			default:
				throw std::runtime_error("invalid operation at this time");
			}

			state = ServiceState::Running;

			return results;
		}
		void EngineService::stop() {
			switch (state) {
			case sani::engine::ServiceState::Suspended:
			case sani::engine::ServiceState::Running:
				onStop();
				break;
			case sani::engine::ServiceState::Stopped:
			case sani::engine::ServiceState::Uninitialized:
			default:
				throw std::runtime_error("invalid operation at this time");
			}

			state = ServiceState::Stopped;
		}

		void EngineService::update(const EngineTime& time) {
			if (state != ServiceState::Running) return;

			onUpdate(time);
		}

		bool EngineService::isUsing(const EngineService* const other) const {
			return std::find(dependencies.begin(), dependencies.end(), other) != dependencies.end();
		}
		bool EngineService::hasHerrors() const {
			return !errors.empty();
		}

		bool EngineService::unuse(EngineService* const other) {
			if (!isUsing(other)) return false;

			dependencies.remove(other);
			
			return true;
		}
		bool EngineService::use(EngineService* const other) {
			if (isUsing(other)) return false;

			dependencies.push_back(other);

			return true;
		}

		EngineService::~EngineService()  {
		}

		bool EngineService::operator == (const EngineService& rhs) const {
			return name == rhs.name && id == rhs.id;
		}
		bool EngineService::operator != (const EngineService& rhs) const {
			return !(*this == rhs);
		}
	}
}