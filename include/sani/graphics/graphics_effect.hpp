#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <list>

SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {

	namespace graphics {

		/// @class EffectUniform graphics_effect.hpp "sani/graphics/graphics_effect.hpp"
		/// @author voidbab
		///
		/// A effect uniform that is contained in the graphics effect.
		class EffectUniform final {
		private:
			const UniformType type;
			const uint32 location;
			const String name;
		public:
			EffectUniform(const UniformType type, const uint32 location, const String& name);

			UniformType getType() const;
			const String& getName() const;
			uint32 getLocation() const;
			
			~EffectUniform() = default;
		};
		
		using UniformList = std::list<EffectUniform>;

		/// @class GraphicsEffect graphics_effect.hpp "sani/graphics/graphics_effect.hpp"
		/// @author voidbab
		///
		/// Represents a graphics effect (shader) that can be used
		/// while rendering.
		class GraphicsEffect final {
		private:
			GraphicsDevice* const device;

			const uint32 effect;

			UniformList uniforms;

			void locateEffectUniforms();
		public:
			GraphicsEffect(GraphicsDevice* const device, const uint32 effect);

			uint32 getEffectID() const;
			
			void listUniforms(UniformList& uniforms);
		
			~GraphicsEffect();
		};
	}
}