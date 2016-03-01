#pragma once

#include "sani/engine/services/renderable_manager.hpp"
#include "sani/platform/time/engine_time.hpp"

namespace sani {

	namespace engine {

		namespace services {
			
			template<class T>
			class UpdatingRenderableManager : public RenderableManager<T> {
			protected:
				UpdatingRenderableManager(const String& name, const renderablemanager::ElementType type, engine::SaNiEngine* const engine);
			public:
				virtual void update(const EngineTime& time) override;

				virtual ~UpdatingRenderableManager() = default;
			};
		}
	}
}

#include "sani/engine/services/impl/updating_renderable_manager.hpp"