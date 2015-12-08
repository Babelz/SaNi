#pragma once

#include "sani/graphics/layer_type.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <vector>
#include <list>

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
			std::vector<graphics::Renderable* const> elements;

			// Bottom part of the layer (all elements that have z value smaller than 0.0f)
			std::vector<graphics::Renderable* const> bottom;
			// Top part of the layer (all elements with z value of 0.0f or greater)
			std::vector<graphics::Renderable* const> top;

			const LayerType type;
			
			bool visible;
			float32 order;
		
			String name;

			void typeInitialize();
		public:
			Layer(const String& name, const LayerType type, const float32 order = 0.0f);

			LayerType getType() const;

			const String& getName() const;
			void setName(const String& name);

			float32 getOrder() const;
			void setOrder(const float32 order);

			bool isVisible() const;
			void hide();
			void show();

			void add(graphics::Renderable* const element);
			void remove(graphics::Renderable* const element);
			
			void render(graphics::Renderer* const renderer);

			~Layer();
		};
	}
}