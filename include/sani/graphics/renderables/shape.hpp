#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include "sani/platform/graphics/color.hpp"
#include "sani/graphics/transformable.hpp"

namespace sani {

	namespace graphics {

		/// @class Shape shape.cpp "sani/graphics/renderables/shape.hpp"
		/// @author voidbab
		///
		/// Abstract base class for all geometric shapes.
		class Shape : public Transformable, public Renderable {
		private:
			Color fill;
		public:
			Shape();
			
			void setFill(const Color& fill);
			const Color& getFill() const;
			
			/*
				TODO: add border color
						- get
						- set
					  add border
						- set thickness
						- get thickness
					  add texturing
						- get 
						- set
			*/
		};
	}
}