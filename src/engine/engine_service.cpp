#include "sani/engine/messaging/state_message.hpp"
#include "sani/engine/engine_service.hpp"

namespace sani {

	namespace engine {

		uint32 EngineService::idGenerator = 0;

		const String initializationErrorMessage		= "initialization failed!";
		const String resumeErrorMessage				= "resume failed!";
		const String suspendErrorMessage			= "failed to suspend the service!";
		const String terminateErrorMessage			= "failed to terminate the service!";

		EngineService::EngineService(const String& name, SaNiEngine* const engine) : name(name),
																					 id(idGenerator++),
																					 engine(engine),
																					 state(ServiceState::Uninitialized) {
		}

		void EngineService::sendStateMessage(StateMessage* const message, const String& errorMessage) {
			handleStateMessage(message);

			if (state == ServiceState::Terminated) {
				// Unsuccesfull terminate messages are handled
				// as fatal errors.
				if (!message->handled) throw std::runtime_error(errorMessage);
				
				return;
			}

			// If message was not handled, terminate the service.
			if (!message->handled) {
				errors.push(errorMessage);

				StateMessage terminateMessage(ServiceState::Terminated, state);

				sendStateMessage(&terminateMessage, terminateErrorMessage);

				state = ServiceState::Terminated;
			}
		}

		void EngineService::handleStateMessage(StateMessage* const stateMessage) {
		}

		SaNiEngine* const EngineService::getEngine() {
			return engine;
		}

		void EngineService::pushError(const String& error) {
			errors.push(error);
		}
		
		void EngineService::start() {
			StateMessage stateMessage(ServiceState::Running, state);

			const String errorMessage = state == ServiceState::Uninitialized ? initializationErrorMessage : resumeErrorMessage;

			sendStateMessage(&stateMessage, errorMessage);
		}
		void EngineService::suspend() {
			StateMessage stateMessage(ServiceState::Suspended, state);

			sendStateMessage(&stateMessage, suspendErrorMessage);
		}
		void EngineService::terminate() {
			StateMessage stateMessage(ServiceState::Terminated, state);
			
			sendStateMessage(&stateMessage, terminateErrorMessage);
		}

		void EngineService::receive(messages::Message* const message) {
		}
		void EngineService::update(const EngineTime& time) {
		}

		ServiceState EngineService::getState() const {
			return state;
		}

		const String& const EngineService::getName() const {
			return name;
		}
		uint32 EngineService::getID() const {
			return id;
		}

		bool EngineService::hasErrors() const {
			return !errors.empty();
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