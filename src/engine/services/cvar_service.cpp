#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/query_message.hpp"
#include "sani/engine/services/contracts/cvar_service_contract.hpp"
#include "sani/engine/messaging/state_message.hpp"
#include "sani/engine/services/cvar_service.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace cvarservice;

			CVarService::CVarService(SaNiEngine* const engine) : EngineService("cvar service", engine) {
			}

			void CVarService::handleStateMessage(StateMessage* const message) {
				if (message->oldState == ServiceState::Uninitialized) {
					initialize();
				} else if (message->newState == ServiceState::Terminated) {
					syncCVars();
				}

				EngineService::handleStateMessage(message);
			}

			void CVarService::handleDocumentMessage(messages::DocumentMessage* const message) {
				const CVarServiceCommands command = static_cast<CVarServiceCommands>(message->getCommand());

				switch (command) {
				case CVarServiceCommands::ListCVars:
					listCVars(message);
					return;
				default:
					// TODO: dead letter.
					return;
				}
			}
			void CVarService::handleQueryMessage(messages::QueryMessage* const message) {
				const CVarServiceCommands command = static_cast<CVarServiceCommands>(message->getCommand());

				switch (command) {
				case CVarServiceCommands::GetCVar:
					getCVar(message);
					return;
				case CVarServiceCommands::ContainsCVar:
					containsCVar(message);
					return;
				default:
					// TODO: dead letter.
					return;
				}
			}

			void CVarService::initialize() {
			}
			void CVarService::syncCVars() {
			}

			void CVarService::generateDefaultConfig() {
			}
			void CVarService::loadConfig() {
			}

			void CVarService::getCVar(messages::QueryMessage* const message) {
			}

			void CVarService::containsCVar(messages::QueryMessage* const message) {
			}

			void CVarService::listCVars(messages::DocumentMessage* const message) {
			}

			void CVarService::receive(messages::Message* const message) {
				const MessageType messageType = message->getType();
				
				switch (messageType) {
				case MessageType::Query:
					handleQueryMessage(static_cast<messages::QueryMessage*>(message));
					break;
				case MessageType::Document:
					handleDocumentMessage(static_cast<messages::DocumentMessage*>(message));
					break;
				default:
					break;
				}
			}
		}
	}
}