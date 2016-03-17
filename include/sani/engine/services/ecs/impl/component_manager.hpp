#pragma once

#include "sani/engine/services/service_logging.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/query_message.hpp"
#include "sani/engine/services/contracts/component_manager_contract.hpp"
#include "sani/engine/services/ecs/component_manager.hpp"
#include "sani/core/utils/convert.hpp"

#include <vector>

namespace sani {

	namespace engine {

		namespace services {

			using namespace componentmanager;

			template <class T>
			ComponentManager<T>::ComponentManager(const String& name, engine::SaNiEngine* const engine)
				: EngineService(name, engine), allocator(256, 1) {
			}

			template <class T>
			const RegisterAllocator<T>& ComponentManager<T>::getAllocator() const {
				return allocator;
			}

			template <class T>
			void ComponentManager<T>::handleDocumentMessage(messages::DocumentMessage* const message) {
				const ComponentManagerCommands command = static_cast<ComponentManagerCommands>(message->getCommand());

				switch (command) {
				case ComponentManagerCommands::CreateComponent:
					createComponent(message);
					break;
				case ComponentManagerCommands::ListComponents:
					listComponents(message);
					break;
				default:
					LOG_DEAD_LETTER(message);
					break;
				}
			}
			template <class T>
			void ComponentManager<T>::handleQueryMessage(messages::QueryMessage* const message) {
				const ComponentManagerCommands command = static_cast<ComponentManagerCommands>(message->getCommand());

				switch (command) {
				case ComponentManagerCommands::DestroyComponent:
					destroyComponent(message);
					break;
				default:
					LOG_DEAD_LETTER(message);
					break;
				}
			}

			template <class T>
			void ComponentManager<T>::createComponent(messages::DocumentMessage* const message) {
				T* component	= nullptr;
				uint32 id		= 0;

				allocator.allocate(component, id);

				component->id = id;

				message->setData(component);
				message->markHandled();
			}
			template <class T>
			void ComponentManager<T>::destroyComponent(messages::QueryMessage* const message) {
				const uint32 id = utils::toInt32(message->getContents());

				allocator.deallocate(id);

				message->markHandled();
			}

			template <class T>
			void ComponentManager<T>::listComponents(messages::DocumentMessage* const message) {
				const std::vector<T*>* elements = allocator.allocatedElements();

				message->setData((void*)elements);
				message->markHandled();
			}

			template <class T>
			void ComponentManager<T>::receive(messages::Message* const message) {
				const MessageType type = static_cast<MessageType>(message->getType());

				switch (type) {
				case MessageType::Document:
					handleDocumentMessage(static_cast<messages::DocumentMessage*>(message));
					break;
				case MessageType::Query:
					handleQueryMessage(static_cast<messages::QueryMessage*>(message));
					break;
				default:
					LOG_DEAD_LETTER(message);
					break;
				}
			}
		}
	}
}