#pragma once

#include "sani/engine/services/contracts/component_manager_contract.hpp"
#include "sani/engine/services/component_manager.hpp"

namespace sani {

	namespace engine {

		namespace services {

			using namespace componentmanager;

			template <class T>
			ComponentManager<T>::ComponentManager(const String& name, engine::SaNiEngine* const engine)
				: EngineService(name, engine) {
			}

			template <class T>
			const RegisterAllocator<T>& ComponentManager<T>::getAllocator() const {
				return allocator;
			}

			template <class T>
			void ComponentManager<T>::handleDocumentMessage(messages::DocumentMessage* const message) {
			}
			template <class T>
			void ComponentManager<T>::handleQueryMessage(messages::DocumentMessage* const message) {
			}

			template <class T>
			void ComponentManager<T>::createComponent(messages::DocumentMessage* const message) {
			}
			template <class T>
			void ComponentManager<T>::destroyComponent(messages::DocumentMessage* const message) {
			}

			template <class T>
			void ComponentManager<T>::listComponents(messages::DocumentMessage* const message) {
			}

			template <class T>
			void ComponentManager<T>::receive(messages::Message* const message) {
				const MessageType type = message->getType();

				switch (type) {
				case MessageType::Document:
					handleDocumentMessage(static_cast<messages::DocumentMessage*>(message));
					break;
				case MessageType::Query:
					handleDocumentMessage(static_cast<messages::QueryMessage*>(message));
					break;
				default:
					// TODO: dead letter.
					break;
				}
			}
		}
	}
}