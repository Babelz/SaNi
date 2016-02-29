#pragma once

#include "sani/platform/graphics/graphics_resource.hpp"
#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/types.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {
	
	namespace graphics {

		/// @class Texture "sani/platform/texture.hpp"
		///
		/// Represents an abstract texture that contains
		/// basic information such as size and id of the
		/// texture.
		class Texture : public GraphicsResource {
		private:
			uint32 width;
			uint32 height;
		protected:
			virtual bool onDispose() override;
		public:
			Texture(GraphicsDevice* device, const uint32 id, const uint32 width, const uint32 height);
			Texture(GraphicsDevice* device, const uint32 width, const uint32 height);
			
			uint32 getWidth() const;
			uint32 getHeight() const;
			
			virtual ~Texture() = default;
		};
	}
}