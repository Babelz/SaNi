#include "sani/engine/services/render_manager.hpp"

namespace sani {

	namespace engine {

		RenderManager(engine::SaNiEngine* const engine, const String& name);

		void applyChanges(T* element);

		void add(T* element);
		void remove(T* element);

		~RenderManager();
	}
}