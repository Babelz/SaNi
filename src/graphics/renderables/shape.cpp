#include "sani/graphics/renderables/shape.hpp"

namespace sani {

	namespace graphics {
		
		Shape::Shape() : Renderable() {
		}

		void Shape::setFill(const Color& fill) {
			this->fill = fill;
		}
		const Color& Shape::getFill() const {
			return fill;
		}
	}
}