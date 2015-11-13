#include "sani/graphics/renderables/renderable.hpp"
#include "sani/resource/texture2d.hpp"

namespace sani {

	namespace graphics {

		void updateGroupIdentifier(Renderable& renderable) {
			for (RenderElementData& renderElementData : renderable.renderData.renderElements) updateGroupIdentifier(renderElementData);
		}
	}
}