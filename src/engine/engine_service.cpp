#include "sani/engine/messaging/state_message.hpp"
#include "sani/engine/services/engine_service.hpp"
#include "sani/core/logging/log.hpp"

#include <sstream>

namespace sani {

	namespace engine {

		namespace services {

			uint32 EngineService::idGenerator = 0;

			static const String initializationErrorMessage		= "initialization failed!";
			static const String resumeErrorMessage				= "resume failed!";
			static const String suspendErrorMessage				= "failed to suspend the service!";
			static const String terminateErrorMessage			= "failed to terminate the service!";

			EngineService::EngineService(const String& name, SaNiEngine* const engine) : name(name),
																						 id(idGenerator++),
																						 engine(engine),
																						 state(ServiceState::Uninitialized) {
			}

			void EngineService::checkIfTerminated(const char* caller) {
				if (state == ServiceState::Terminated) {
					std::stringstream ss;
					ss << "invalid function call ";
					ss << "\"";
					ss << caller;
					ss << "\"";
					ss << ", service has been terminated";

					FNCLOG_ERR(log::OutFlags::All, ss.str());

					std::abort();
				}
			}

			SaNiEngine* const EngineService::getEngine() {
				return engine;
			}

			bool EngineService::onStart() {
				return true;
			}
			bool EngineService::onResume() {
				return true;
			}
			void EngineService::onSuspend() {
			}
			void EngineService::onTerminate() {
			}

			bool EngineService::start() {
				checkIfTerminated(__FUNCTION__);

				bool results = false;

				if		(state == ServiceState::Uninitialized)	results = onStart();
				else if (state == ServiceState::Suspended)		results = onResume();
				else											FNCLOG_WRN(log::OutFlags::All, "call to start invalid at this time");

				if (results) state = ServiceState::Running;

				return results;
			}
			void EngineService::suspend() {
				checkIfTerminated(__FUNCTION__);

				if (state != ServiceState::Running) {
					FNCLOG_WRN(log::OutFlags::All, "call to suspend invalid at this time");
					
					return;
				}

				onSuspend();
				
				state = ServiceState::Suspended;
			}
			void EngineService::terminate() {
				checkIfTerminated(__FUNCTION__);

				std::stringstream ss;
				ss << "service ";
				ss << "\"";
				ss << getName();
				ss << "\" ";
				ss << "terminated";

				FNCLOG_INF(log::OutFlags::All, ss.str());

				onTerminate();

				state = ServiceState::Terminated;
			}

			void EngineService::receive(messages::Message* const message) {
			}
			void EngineService::update(const EngineTime& time) {
			}

			ServiceState EngineService::getState() const {
				return state;
			}

			const String& EngineService::getName() const {
				return name;
			}
			uint32 EngineService::getID() const {
				return id;
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
}