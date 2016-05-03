#pragma once

#include "sani/core/events.hpp"

#include "sani/graphics/layer_type.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);
SANI_FORWARD_DECLARE_2(sani, graphics, Renderable);
SANI_FORWARD_DECLARE_2(sani, graphics, Renderer);

namespace sani {

	namespace graphics {

		/// @class Layer layer.hpp "sani/graphics/layer.hpp"
		/// @author voidbab
		///
		/// Groups elements together for rendering.
		class Layer {
		private:

			// Bottom part of the layer (all elements that have z value smaller than 0.0f)
			std::vector<graphics::Renderable* const> bottom;
			// Top part of the layer (all elements with z value of 0.0f or greater)
			std::vector<graphics::Renderable* const> top;

			const LayerType type;
			
			bool visible;
			float32 order;
		
			String name;

			void typeInitialize();

			void renderBottom(graphics::Renderer* const renderer);
			void renderTop(graphics::Renderer* const renderer);
		public:


			Layer(const String& name, const LayerType type, const float32 order = 0.0f);
			
			/// Returns the layers type. 
			LayerType getType() const;

			//// Returns the display name of the layer.
			const String& getName() const;
			/// Sets the name of the layer.
			void setName(const String& name);

			/// Returns the draw order of the layer.
			float32 getOrder() const;
			/// Sets the draw order of the layer.
			void setOrder(const float32 order);

			/// Returns true if the layer is currently visible.
			bool isVisible() const;
			/// Hides the layer.
			void hide();
			/// Makes the layer visible.
			void show();

			/// Add new element to this layer.
			void add(graphics::Renderable* const element);
			/// Remove given element from this layer.
			void remove(graphics::Renderable* const element);
			
			/// Draws this layer to the screen.
			void render(graphics::Renderer* const renderer);

			/// Moves elements from this layer to new layer.
			/// Causes all the elements to be removed from this layer.
			void moveElementsTo(Layer* const other);

			~Layer();

			bool operator ==(const Layer& lhs) const;
			bool operator !=(const Layer& lhs) const;
		};
	}
}