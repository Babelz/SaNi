#include "sani/graphics/renderables/renderable.hpp"
#include "sani/resource/texture2d.hpp"

namespace sani {

	namespace graphics {

		void updateHash(Renderable& renderable) {
			for (RenderElementData& renderElementData : renderable.renderData.renderElements) updateHash(renderElementData);
		}
	}
}