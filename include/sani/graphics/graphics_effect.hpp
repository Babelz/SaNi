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
			GraphicsDevice* const device;
			
			const uint32 effect;
			const UniformType type;
			const uint32 location;
			const String name;
		public:
			EffectUniform(GraphicsDevice* const device, const uint32 effect, const UniformType type, const uint32 location, const String& name);

			UniformType getType() const;
			const String& getName() const;
			uint32 getLocation() const;
			void setData(void* data);
			
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
			GraphicsDevice* device;

			uint32 effect;

			UniformList uniforms;

			void locateEffectUniforms();
		public:
			/// Creates new effect instance. Using this constructor
			/// requires the given effect to be compiled.
			/// @param[in] device the graphics device
			/// @param[in] effect the API specific effect "name" or "id".
			GraphicsEffect(GraphicsDevice* const device, const uint32 effect);
			GraphicsEffect(GraphicsEffect& other);
			GraphicsEffect();

			/// Returns the effect to the caller.
			uint32 getEffect() const;
			
			/// Lists the uniforms this effect contains.
			void listUniforms(UniformList& uniforms) const;
			/// Returns true if the effect contains uniform with given name.
			bool containsUniform(const String& name) const;
			/// Returns the uniform with given name. If no
			/// uniform is found with the given name, the 
			/// function will return a nullptr.
			EffectUniform* const findUniform(const String& name);
			
			/// Causes this effect to be applied to the rendering process.
			/// Has no effect if the effect is created via the default ctro.
			void bind();
			/// Unbinds this effect. The effect will be binded 
			/// until this function is called or some other 
			/// effect gets binded via the graphics device.
			/// Has no effect if the effect is created via the default ctro.
			void unbind();

			~GraphicsEffect();

			static GraphicsEffect compile(GraphicsDevice* const device, const String& vertexSource, const String& fragmentSource);

			GraphicsEffect& operator =(const GraphicsEffect& other);
		};
	}
}