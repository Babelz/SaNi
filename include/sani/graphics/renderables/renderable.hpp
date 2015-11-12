#pragma once

#include "sani/graphics/render_data.hpp"
#include "sani/core/math/rectangle.hpp"
#include "sani/graphics/Transform.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		class Texture2D;
		class Renderer;
		
		/// @class Renderable renderable.hpp "sani/graphics/renderable.hpp"
		/// @author voidbab
		/// 
		/// Interface for objects that can be rendered to the screen. Contains texture,
		/// transform and bound data. 
		class Renderable {
		public:
			RenderData renderData;
			Transform transform;

			math::Rectf globalBounds;
			math::Rectf localBounds;

			math::Rectf sourceRectangle;
			Texture2D* texture;

			Renderable(const uint32 vertices, const uint32 indices, const uint32 renderElements);
			Renderable(const uint32 vertices, const uint32 renderElements);

			~Renderable();

			/*
				Common interface operations between renderables:
					- recomputeVertices
					- recomputeBounds
					- canRender
			*/
		};
	}
}