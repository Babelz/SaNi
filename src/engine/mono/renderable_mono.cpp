#include "sani/engine/mono/renderable_mono.hpp"
#include "sani/engine/mono/mono_include.hpp"

namespace sani {

	namespace engine {
		
		namespace mono {

			RenderableSuperDef::RenderableSuperDef(const String name, const String ns) : name(name),
																						 ns(ns) {
			}

			bool registerRenderableMembers(const RenderableSuperDef& def) {
				// Check that all properties have internal calls.
				MONO_BASE_DEF_CHECK_FOR_NULL(transform, def);
				MONO_BASE_DEF_CHECK_FOR_NULL(localBounds, def);
				MONO_BASE_DEF_CHECK_FOR_NULL(globalBounds, def);
				MONO_BASE_DEF_CHECK_FOR_NULL(texture2D, def);
				
				MONO_REGISTER_PROPERTY(def.ns.c_str(), def.name.c_str(), def.transform)
				MONO_REGISTER_PROPERTY(def.ns.c_str(), def.name.c_str(), def.localBounds)
				MONO_REGISTER_PROPERTY(def.ns.c_str(), def.name.c_str(), def.globalBounds)
				MONO_REGISTER_PROPERTY(def.ns.c_str(), def.name.c_str(), def.texture2D)
				
				return false;
			}
		}
	}
}