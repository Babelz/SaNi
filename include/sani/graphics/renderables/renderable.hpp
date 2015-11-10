#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/Transform.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/core/math/rectangle.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);
namespace sani {

	namespace graphics {
		class Renderer;
		
		/*
			Document DOD, hierarchy, architecture etc.

			If the object has getters/setters for specific operation,
			do use them or you are a moron.

			(RESPECT THE INTERFACE!)
		*/

		/// @class Renderable renderable.hpp "sani/graphics/renderable.hpp"
		/// @author voidbab
		/// 
		/// Interface for objects that can be rendered to the screen. Contains texture,
		/// transform and bound data. 
		class Renderable {
		public:
			Transform transform;

			math::Rectf sourceRectangle;
			math::Rectf globalBounds;
			math::Rectf localBounds;

			resource::Texture2D* texture;

			Renderable();

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