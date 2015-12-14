#include "sani/engine/services/renderable_manager.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			template <class T>
			RenderableManager<T>::RenderableManager(const String& name, const ElementType type, engine::SaNiEngine* const engine) : EngineService(name, engine),
																																	type(type) {
			}

			template <class T>
			void RenderableManager<T>::handleDocumentMessage(messages::DocumentMessage* const message) {
			}
			template <class T>
			void RenderableManager<T>::handleCommandMessage(messages::CommandMessage* const message) {
			}

			template <class T>
			void RenderableManager<T>::createElement(messages::DocumentMessage* const message) {
			}
			template <class T>
			void RenderableManager<T>::deleteElement(messages::DocumentMessage* const message) {
			}
			template <class T>
			void RenderableManager<T>::createElement(messages::CommandMessage* const message) {
			}

			template <class T>
			void RenderableManager<T>::getElements(messages::DocumentMessage* const message) {
			}

			template <class T>
			void RenderableManager<T>::receive(messages::Message* const message) {
			}
			template <class T>
			void RenderableManager<T>::update(const SaNiEngine& time) {
			}
		}
	}
}