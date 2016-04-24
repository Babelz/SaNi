#include "sani/engine/mono/mono_include.hpp"
#include "sani/engine/mono/texture2d_mono.hpp"
#include "sani/resource/texture2d.hpp"

#include <vector>

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(texture2d)

		struct Texture2DMono final {
			sani::resource::Texture2D*	nativeptr;
			MonoString*					managedptr;

			Texture2DMono(sani::resource::Texture2D* const nativeptr, MonoString* const managedptr) : nativeptr(nativeptr),
																									  managedptr(managedptr) {
			}
		};

		std::vector<Texture2DMono> instances;

		static Texture2DMono* getInstance(MonoString* instance) {
			for (auto& texture2DMono : instances) if (texture2DMono.managedptr == instance) return &texture2DMono;

			return nullptr;
		}

		static gint32 InternalGetWidth(MonoString* instance) {
			return static_cast<gint32>(getInstance(instance)->nativeptr->getWidth());
		}
		static gint32 InternalGetHeight(MonoString* instance) {
			return static_cast<gint32>(getInstance(instance)->nativeptr->getHeight());
		}
		static gint32 InternalGetID(MonoString* instance) {
			return static_cast<gint32>(getInstance(instance)->nativeptr->getID());
		}
		static gboolean InternalGetDisposed(MonoString* instance) {
			return static_cast<gboolean>(getInstance(instance)->nativeptr->disposed());
		}

		MonoObject* createTexture2D() {
			const MonoClassDefinition texture2DDef("SaNi.Mono.Graphics", "Texture2D");

			return MONO_PROVIDER->createObject(&texture2DDef);
		}

		MonoObject* getManagedPtr(const uint32 id) {
			for (auto& texture2DMono : instances) if (texture2DMono.nativeptr->getID() == id) return (MonoObject*)texture2DMono.managedptr;

			return nullptr;
		}
		sani::resource::Texture2D* getNativePtr(MonoString* managedptr) {
			for (auto& texture2DMono : instances) if (texture2DMono.managedptr == managedptr) return texture2DMono.nativeptr;
			
			return nullptr;
		}

		void registerTexture2D(sani::resource::Texture2D* const nativeptr, MonoObject* const managedptr) {
			instances.push_back(Texture2DMono(nativeptr, (MonoString*)managedptr));
		}
		void unregisterTexture2D(sani::resource::Texture2D* const nativeptr, MonoObject* const managedptr) {
			auto it = std::find_if(instances.begin(), instances.end(), [&managedptr](Texture2DMono& t) {
				return (MonoString*)managedptr == t.managedptr;
			});

			instances.erase(it);
		}

		bool initialize() {
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Texture2D, InternalGetWidth, InternalGetWidth);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Texture2D, InternalGetHeight, InternalGetHeight);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Texture2D, InternalGetID, InternalGetID);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Texture2D, InternalGetDisposed, InternalGetDisposed);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}