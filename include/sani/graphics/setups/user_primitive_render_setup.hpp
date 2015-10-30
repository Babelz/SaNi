#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/setups/render_setup.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		/// @class 
		class UserPrimitiveRenderSetup : public RenderSetup {
		private:
			RenderMode renderMode;

			uint32 vertices;
		public:
			UserPrimitiveRenderSetup(GraphicsDevice* const graphicsDevice);

			void setRenderMode(const RenderMode renderMode);
			RenderMode getRenderMode() const;

			void setVertices(const uint32 vertices);
			uint32 getVertices() const;
			
			virtual void use() override;

			virtual void clear() override;
		};
	}
}