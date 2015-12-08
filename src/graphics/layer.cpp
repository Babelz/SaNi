#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/layer.hpp"

namespace sani {

	namespace graphics {

		Layer::Layer(const String& name, const LayerType type, const float32 order = 0.0f) : name(name), 
																							 type(type),
																							 order(order),
																							 visible(true) {
			typeInitialize();
		}

		void Layer::typeInitialize() {
			if (type == LayerType::Static) throw std::runtime_error("unsupported");
		}
		
		LayerType Layer::getType() const { 
			return type;
		}

		const String& Layer::getName() const {
			return name;
		}
		void Layer::setName(const String& name) {
			this->name = name;
		}

		float32 Layer::getOrder() const {
			return order;
		}
		void Layer::setOrder(const float32 order) {
			this->order = order;
		}

		bool Layer::isVisible() const {
			return visible;
		}
		void Layer::hide() {
			visible = false;
		}
		void Layer::show() {
			visible = true;
		}

		void Layer::add(graphics::Renderable* const element) {
			if (element->transform.position.z < 0.0f)	bottom.push_back(element);
			else										top.push_back(element);
		}
		void Layer::remove(graphics::Renderable* const element) {
			if (element->transform.position.z < 0.0f)	bottom.erase(std::find(bottom.begin(), bottom.end(), element));
			else										top.erase(std::find(top.begin(), top.end(), element));
		}

		void Layer::render(graphics::Renderer* const renderer) {
			if (bottom.size() > 0)	renderer->renderElements(bottom.data()[0], bottom.size());
			if (top.size() > 0)		renderer->renderElements(top.data()[0], top.size());
		}

		Layer::~Layer() {
		}
	}
}