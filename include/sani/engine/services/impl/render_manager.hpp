#include "sani/graphics/renderables/renderables.hpp"
#include "sani/engine/services/render_manager.hpp"

namespace sani {

	namespace engine {

		template<class T>
		RenderManager<T>::RenderManager(engine::SaNiEngine* const engine, const String& name) : EngineService(engine, name) {
			modifiedElements.reserve(32);
			elements.reserve(32);
		}
		
		template<class T>
		uint32 RenderManager<T>::nextElementIndex() {
			uint32 nextIndex = 0;

			if (releasedElementIndices.empty()) nextIndex = elements.size();
			else {
				nextIndex = releasedElementIndices.top();

				releasedElementIndices.pop();
			}

			return nextIndex;
		}

		template<class T>
		void RenderManager<T>::onUpdate(const EngineTime& time) {
			if (modifiedElementIndices.empty()) return;

			while (!modifiedElementIndices.empty()) {
				const uint32 index = modifiedElementIndices.top();
				
				T* const element = elements[index];
				graphics::recomputeBounds(element);
				graphics::recomputeVertices(element);
				graphics::updateRenderData(element);
				
				modifiedElementIndices.pop();
			}
		}

		template<class T>
		void RenderManager<T>::applyChanges(T* element) {
			modifiedElementIndices.push(element->location);
		}

		template<class T>
		void RenderManager<T>::add(T* const element) {
			const uint32 elementIndex = nextElementIndex()
			element->location = elementIndex;

			if	 (elementIndex == elements.size()) elements.push_back(element);
			else								   elements[elementIndex] = element;
		}
		template<class T>
		void RenderManager<T>::remove(T* const element) {
			const uint32 elementIndex = element->nextElementIndex();

			elements.erase(elements.begin() + elementIndex);

			releasedElementIndices.push(elementIndex);
		}

		template<class T>
		RenderManager<T>::~RenderManager() {
		}
	}
}