#pragma once

#include "sani/engine/services/updating_renderable_manager.hpp"

namespace sani {

	namespace engine {

		namespace services {

			template<class T>
			UpdatingRenderableManager<T>::UpdatingRenderableManager(const String& name, const renderablemanager::ElementType type, engine::SaNiEngine* const engine)
				: RenderableManager<T>(name, type, engine) {
			}

			template<class T>
			void UpdatingRenderableManager<T>::update(const EngineTime& time) {
				RenderableManager<T>::update(time);

				const RegisterAllocator<T>& allocator = getAllocator();
				const std::vector<T*>* renderables = allocator.allocatedElements();

				auto it = renderables->begin();

				while (it != renderables->end()) {
					T* renderable = *it;

					// Pass by pointer.
					graphics::update(renderable, time);

					it++;
				}
			}
		}
	}
}