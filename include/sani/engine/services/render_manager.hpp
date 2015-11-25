#pragma once

#include "sani/engine/engine_service.hpp"
#include "sani/types.hpp"

#include <vector>
#include <stack>

namespace sani {

	namespace engine {
		
		template<class T>
		class RenderManager : public EngineService {
		private:
			std::stack<const uint32> modifiedElementIndices;
			std::stack<const uint32> releasedElementIndices;
			
			std::vector<T*> elements;

			uint32 nextElementIndex();
		protected:
			void onUpdate(const EngineTime& time) override;
		public:
			RenderManager(engine::SaNiEngine* const engine, const String& name);

			void applyChanges(T* element);
			
			void add(T* element);
			void remove(T* element);

			~RenderManager();
		};
	}
}

#include "sani/engine/services/impl/render_manager.hpp"