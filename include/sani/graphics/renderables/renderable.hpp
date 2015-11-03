#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/render_state.hpp"
#include "sani/core/math/rectangle.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		class Renderer;
		
		/// @class Renderable renderable.hpp "sani/graphics/renderable.hpp"
		/// @author voidbab
		/// 
		/// Interface for objects that can render
		/// themselves to the screen.
		class Renderable  { 
		public:
			Renderable() = default;

			/// Returns the local bounds of the object.
			virtual const math::Rectf getLocalBounds() const = 0;
			/// Returns the global bounds of the object.
			virtual const math::Rectf getGlobalBounds() const = 0;
			
			/// Causes this object to render itself to the screen.
			/// @param[in] renderer the low-level renderer the object will use to render itself
			virtual void render(Renderer* const renderer) = 0;

			virtual ~Renderable() = default;
		};
	}
}