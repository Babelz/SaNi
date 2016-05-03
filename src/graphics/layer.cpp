#include "sani/graphics/renderables/renderable.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/graphics/layer.hpp"
#include "sani/core/logging/log.hpp"

namespace sani {

	namespace graphics {

		Layer::Layer(const String& name, const LayerType type, const float32 order) : name(name), 
																					  type(type),
																					  order(order),
																					  visible(true) {
			typeInitialize();
			
			SANI_INIT_EVENT(orderChanged, void());
		}

		void Layer::typeInitialize() {
			if (type == LayerType::Static) {
				FNCLOG_ERR(log::OutFlags::All, "unsupported layer type static");
				
				std::abort();
			}
		}

		void Layer::renderBottom(sani::graphics::Renderer* const renderer) {
			if (bottom.size() == 0) return;

			for (graphics::Renderable* const renderable : bottom) renderer->renderElement(renderable);
		}
		void Layer::renderTop(sani::graphics::Renderer* const renderer) {
			if (top.size() == 0) return;
			
			for (graphics::Renderable* const renderable : top) renderer->renderElement(renderable);
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

			SANI_TRIGGER_VOID_EVENT(orderChanged, void());
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
			renderBottom(renderer);
			renderTop(renderer);
		}

		void Layer::getElements(std::vector<graphics::Renderable* const>& outElements) {
			outElements.reserve(top.size() + bottom.size());

			std::move(top.begin(), top.end(), outElements.begin());
			std::move(bottom.begin(), bottom.end(), outElements.begin() + top.size());

			//// TODO: do with move.

			//for (auto element : top)	outElements.push_back(element);
			//for (auto element : bottom) outElements.push_back(element);

			//top.clear();
			//bottom.clear();
		}
		uint32 Layer::elementsCount() const {
			return top.size() + bottom.size();
		}

		Layer::~Layer() {
		}

		bool Layer::operator ==(const Layer& lhs) const {
			return lhs.getName() == name;
		}
		bool Layer::operator !=(const Layer& lhs) const {
			return !(lhs.getName() == name);
		}

		Layer& Layer::operator =(Layer& lhs) {
			std::swap(lhs.bottom, bottom);
			std::swap(lhs.top, top);
			std::swap(lhs.type, type);
			std::swap(lhs.visible, visible);
			std::swap(lhs.order, order);
			std::swap(lhs.name, name);

			return *this;
		}
	}
}