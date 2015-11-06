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
		
		/// @class Renderable renderable.hpp "sani/graphics/renderable.hpp"
		/// @author voidbab
		/// 
		/// Interface for objects that can render
		/// themselves to the screen.
		class Renderable : public Transformable {
		private:
			math::Rectf globalBounds;
			math::Rectf localBounds;

			uint32 verticesCount;
		public:
			Renderable() = default;

			/// Returns the local bounds of the object.
			virtual const math::Rectf& getLocalBounds() const = 0;
			/// Returns the global bounds of the object.
			virtual const math::Rectf& getGlobalBounds() const = 0;
			
			/// Causes this object to render itself to the screen.
			/// @param[in] renderer the low-level renderer the object will use to render itself
			virtual void render(Renderer* const renderer) = 0;

			/// Causes the renderable element to recompute it's 
			/// vertices. Should be called before any rendering operations.
			virtual void recomputeVertices() = 0;

			// TODO: implement texturing when content works.
			//void setTexture(const Texture2D* const texture);
			//const Texture2D* getTexture() const;

			//void setTextureRext(const math::Rectf& rectangle);
			//const math::Rectf& getTextureRect() const;

			/// Returns true if the renderers state allows this
			/// element to be renderer.
			///
			/// TODO: too much overhead? 
			//virtual bool canRender(const Renderer* const renderer) const = 0;

			virtual ~Renderable() = default;
		};
	}
}