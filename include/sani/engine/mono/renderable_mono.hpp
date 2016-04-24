#pragma once

/*
	Contains common renderable internal call hookings for all classes
	that implement the interface IRenderable.
*/

#include "sani/engine/mono/mono_define.hpp"
#include "sani/types.hpp"

#include "sani/engine/mono/glib_types.hpp"
#include <mono/metadata/object.h>
#include <functional>

namespace sani {

	namespace engine {
		
		namespace mono {
		
			struct RenderableSuperDef final {
				const String name;
				const String ns;

				/*
					IRenderable member properties
				*/

				MonoPropertyDefinition<MonoObject*> transform		{ "Transform", PropsGetSet };
				MonoPropertyDefinition<MonoObject*> localBounds		{ "LocalBounds", PropsGetSet };
				MonoPropertyDefinition<MonoObject*> globalBounds	{ "GlobalBounds", PropsGet };
				MonoPropertyDefinition<MonoObject*> textureSource	{ "TextureSource", PropsGetSet };
				MonoPropertyDefinition<MonoObject*> texture2D		{ "Texture2D", PropsGetSet };
				MonoPropertyDefinition<gboolean>	visible			{ "Visible", PropsGetSet };

				RenderableSuperDef(const String name, const String ns);

				~RenderableSuperDef() = default;
			};

			bool registerRenderableMembers(const RenderableSuperDef& def);
		}
	}
}