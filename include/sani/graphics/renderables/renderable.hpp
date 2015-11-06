#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/transformable.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/core/math/rectangle.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		/*class Texture2D;*/
		class Renderer;
		class Texture2D;

		/// @class Renderable renderable.hpp "sani/graphics/renderable.hpp"
		/// @author voidbab
		/// 
		/// Interface for objects that can render
		/// themselves to the screen.
		class Renderable {
		public:
			Transformable transform;

			math::Rectf globalBounds;
			math::Rectf localBounds;

			Texture2D* texture;

			Renderable();

			~Renderable();
		};

		inline bool canRender(const Renderable* const renderable, const Renderer* const renderer);

		/// Causes this object to render itself to the screen.
		/// @param[in] renderer the low-level renderer the object will use to render itself
		inline void render(const Renderable* const renderable, Renderer* const renderer);

		/// Causes the renderable element to recompute it's 
		/// vertices. Should be called before any rendering operations.
		inline void recomputeVertices(Renderable* const renderable);
	}
}

#include "sani/graphics/inl/renderable.inl"