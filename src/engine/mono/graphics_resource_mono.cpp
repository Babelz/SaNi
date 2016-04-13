#include "sani/engine/mono/mono_define.hpp"
#include "sani/core/logging/log.hpp"

#include "sani/engine/mono/mono_runtime.hpp"
#include "sani/engine/mono/mono_provider.hpp"
#include "sani/engine/mono/glib_types.hpp"
#include "mono/metadata/object.h"

#include "sani/engine/sani_engine.hpp"

#include "sani/engine/mono/graphics_resource_mono.hpp"

#include "sani/core/utils/string_utils.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(graphicsresource)

			//struct GraphicsResourceMono final {
			//	sani::graphics::GraphicsResource* resource{ nullptr };
			//	MonoString* instance{ nullptr };

			//	GraphicsResourceMono() = default;
			//	~GraphicsResourceMono() = default;
			//};


			//std::vector<GraphicsResourceMono> graphicsResources;
			//static MonoClass* mclass;

			//static GraphicsResourceMono* const findGraphicsResource(MonoString* instance) {
			//	for (auto& graphicsResource : graphicsResources) {
			//		if (graphicsResource.instance == instance) return &graphicsResource;
			//	}

			//	return nullptr;
			//}

			//static gint32 InternalGetID(MonoString* instance) {
			//	GraphicsResourceMono* const graphicsResource = findGraphicsResource(instance);

			//	return static_cast<gint32>(graphicsResource->resource->getID());
			//}
			//static gboolean InternalGetDisposed(MonoString* instance) {
			//	GraphicsResourceMono* const graphicsResource = findGraphicsResource(instance);

			//	return static_cast<gboolean>(graphicsResource->resource->disposed());
			//}

			//void createResource(sani::graphics::GraphicsResource* const resource) {
			//}
			//void releaseResource(sani::graphics::GraphicsResource* const resource) {
			//}

			bool initialize() {
				//MONO_DEFINE_CLASS(SaNi.Mono.Graphics, GraphicsResource);

				//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsResource, InternalGetID, NO_ARGS, InternalGetID);
				//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, GraphicsResource, InternalGetDisposed, NO_ARGS, InternalGetDisposed);

				return true;
			}

		MONO_MODULE_IMPL_END
	}
}