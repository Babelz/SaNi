#pragma once

#include "sani/graphics/render_data.hpp"
#include "sani/core/math/rectangle.hpp"
#include "sani/graphics/Transform.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

namespace sani {

	namespace graphics {

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

			math::Rectf textureSource;
			resource::Texture2D* texture;

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

		inline void updateGroupIdentifier(Renderable& renderable);
	}
}

#include "sani/graphics/inl/renderable.inl"