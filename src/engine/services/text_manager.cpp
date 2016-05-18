#include "sani/engine/services/text_manager.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			TextManager::TextManager(SaNiEngine* const engine) : RenderableManager<graphics::Text>("text manager", ElementType::Text, engine) {
			}
		}
	}
}