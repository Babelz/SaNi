#pragma once

#include "sani/engine/engine_service.hpp"
#include "sani/types.hpp"

#include <vector>
#include <stack>

namespace sani {

	namespace engine {
		
		/// @class RenderManager render_manager.cpp "sani/engine/services/render_manager.hpp"
		/// @author voidbab
		/// 
		/// Small service that is responsible of updating 
		/// renderable elements when they require updating.
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

			/// Adds given element to the update queue.
			void applyChanges(T* element);
			
			/// Adds given element to the manager.
			void add(T* element);
			/// Removes given element from the manager.
			void remove(T* element);

			/// Clears the manager.
			void clear();

			~RenderManager();
		};
	}
}

#include "sani/engine/services/impl/render_manager.hpp"