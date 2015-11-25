#include "sani/graphics/renderables/renderables.hpp"
#include "sani/engine/engine_service.hpp"
#include "sani/forward_declare.hpp"

#include <list>

SANI_FORWARD_DECLARE_2(sani, graphics, Renderer);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {

	namespace engine {

		class RenderService : public EngineService {
		private:
			std::list<graphics::Renderable*> elements;

			graphics::GraphicsDevice* graphicsDevice;
			graphics::Renderer* renderer;
		protected:
			bool onInitialize() override;

			void onUpdate(const EngineTime& time) override;
		public:
			RenderService(SaNiEngine* const engine, graphics::GraphicsDevice* const graphicsDevice);

			/*
				TODO: impl
				- layers
				- culling
				- element updates
				- make fast af...
			*/

			void addElement(graphics::Renderable* const renderable);
			void removeElement(graphics::Renderable* const renderable);

			virtual ~RenderService() override;
		};
	}
}