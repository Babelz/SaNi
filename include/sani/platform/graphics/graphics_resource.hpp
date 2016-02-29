#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {

	namespace graphics {

		/// @class GraphicsResource graphics_resource.hpp "sani/platform/graphics/graphics_resource.hpp"
		/// @author voidbab
		///
		/// Represents a graphics resource.
		class GraphicsResource {
		private:
			bool disposeCalled;
			bool wasdDisposed;

			uint32 id;

			GraphicsDevice* device;
		protected:
			GraphicsDevice* const getDevice();

			virtual bool onDispose() = 0;
			
			void setID(const uint32 id);
		public:
			GraphicsResource(GraphicsDevice* const device);

			/// Disposes the resource.
			void dispose();

			/// Returns true if the resource has been disposed.
			bool disposed() const;

			uint32 getID() const;

			virtual ~GraphicsResource() = default;

			bool operator ==(const GraphicsResource& rhs) const;
			bool operator !=(const GraphicsResource& rhs) const;
		};
	}
}