#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/viewport.hpp"

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <list>
#include <unordered_map>
#include <tuple>

SANI_FORWARD_DECLARE_2(sani, graphics, RenderTarget2D);

namespace sani {

	namespace graphics {

		/// @class GraphicsDeviceState graphics_device_state.hpp "sani/platform/graphics/graphics_device_state.hpp"
		/// @author voidbab
		/// 
		/// Contains the state data of the graphics device.
		class GraphicsDeviceState final {
		public:
			std::unordered_map<uint32, VertexAttributePointerDescription> vertexPointers;
			std::unordered_map<BufferType, uint32> bindedBuffers;

			RenderTarget2D* renderTarget;
			Viewport viewport;

			uint32 texture;
			uint32 shader;
			
			GraphicsDeviceState();
			
			~GraphicsDeviceState() = default;
		};
	}
}