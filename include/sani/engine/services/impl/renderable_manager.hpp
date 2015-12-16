#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/services/renderable_manager.hpp"
#include "sani/graphics/renderables/renderables.hpp"
#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace renderablemanager;

			template <class T>
			RenderableManager<T>::RenderableManager(const String& name, const ElementType type, engine::SaNiEngine* const engine) : EngineService(name, engine),
																																	type(type),
																																	allocator(PagePoolAllocator<T>(256)) {
			}

			template <class T>
			void RenderableManager<T>::handleDocumentMessage(messages::DocumentMessage* const message) {
				const RenderableManagerCommands command = static_cast<RenderableManagerCommands>(message->getCommand());

				switch (command) {
				case RenderableManagerCommands::CreateElement:
					createElement(message);
					return;
				case RenderableManagerCommands::DeleteElement:
					deleteElement(message);
					return;
				case RenderableManagerCommands::GetElements:
					getElements(message);
					return;
				default:
					return;
				}
			}
			
			template <class T>
			void RenderableManager<T>::createElement(messages::DocumentMessage* const message) {
				T* element = allocator.allocate();
				
				elements.push_back(element);

				message->setData(element);
				message->markHandled();
			}
			template <class T>
			void RenderableManager<T>::deleteElement(messages::DocumentMessage* const message) {
				T* element = static_cast<T*>(message->getData());

				allocator.deallocate(element);

				elementsToUpdate.remove(element);

				message->markHandled();
			}
			template <class T>
			void RenderableManager<T>::queueForUpdates(messages::DocumentMessage* const message) {
				T* element = static_cast<T*>(message->getData());

				elementsToUpdate.push_back(element);
				
				message->markHandled();
			}

			template <class T>
			void RenderableManager<T>::getElements(messages::DocumentMessage* const message) {
				std::list<T* const>* results = getEngine()->allocateShared<std::list<T* const>>();
				SANI_NEW_DYNAMIC_DEFAULT(std::list<T* const>, results);

				for (T* const element : elements) results->push_back(element);

				message->setData(results);
				message->markHandled();
			}

			template <class T>
			void RenderableManager<T>::receive(messages::Message* const message) {
				if (message->getType() == MessageType::Document) {
					handleDocumentMessage(static_cast<messages::DocumentMessage* const>(message));
				}
			}
			template <class T>
			void RenderableManager<T>::update(const EngineTime& time) {
				if (elementsToUpdate.empty()) return;

				for (T* const element : elementsToUpdate) {
					recomputeVertices(*element);
					recomputeBounds(*element);

					updateRenderData(*element);
				}

				elementsToUpdate.clear();
			}
		}
	}
}