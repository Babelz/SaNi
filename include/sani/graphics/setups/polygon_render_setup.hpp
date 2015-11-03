#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/setups/render_setup.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		/// @class 
		class PolygonRenderSetup : public RenderSetup {
		private:
			RenderMode renderMode;

			uint32 elements;
		public:
			PolygonRenderSetup(GraphicsDevice* const graphicsDevice);

			void setRenderMode(const RenderMode renderMode);
			RenderMode getRenderMode() const;

			void setElements(const uint32 elements);
			uint32 getElements() const;
			
			virtual void use() override;

			virtual void clear() override;
		};
	}
}