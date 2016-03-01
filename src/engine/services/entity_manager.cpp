#include "sani/engine/services/contracts/entity_manager_contract.hpp"
#include "sani/engine/services/entity_manager.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/message.hpp"
#include "sani/ecs/entity.hpp"

namespace sani {

	namespace engine {

		namespace services {
		
			using namespace entitymanager;

			EntityManager::EntityManager(SaNiEngine* const engine) 
				: EngineService("entity manager", engine), allocator(512, 1) {
			}

			void EntityManager::handleDocumentMessage(messages::DocumentMessage* const message) {
				const EntityManagerCommands command = static_cast<EntityManagerCommands>(message->getCommand());
				
				switch (command) {
				case EntityManagerCommands::CreateEntity:
					createEntity(message);
					break;
				case EntityManagerCommands::DestroyEntity:
					destroyEntity(message);
					break;
				case EntityManagerCommands::ListEntities:
					listEntities(message);
					break;
				default:
					break;
				}
			}

			void EntityManager::createEntity(messages::DocumentMessage* const message) {
				Entity* entity	= nullptr;
				uint32 id		= 0;

				allocator.allocate(entity, id);

				entity->id = id;

				message->setData(entity);
				message->markHandled();
			}
			void EntityManager::destroyEntity(messages::DocumentMessage* const message) {
				// TODO: 
				//	- destroy components
				//  - destroy entity
			}

			void EntityManager::listEntities(messages::DocumentMessage* const message) {
				const std::vector<Entity*>* results = allocator.allocatedElements();

				message->setData((void*)results);
				message->markHandled();
			}

			void EntityManager::receive(messages::Message* const message) {
				const MessageType type = message->getType();

				switch (type) {
				case MessageType::Document:
					handleDocumentMessage(static_cast<messages::DocumentMessage*>(message));
					break;
				default:
					// TODO: dead letter.
					break;
				}
			}
		}
	}
}