#include "sani/engine/mono/mono_include.hpp"
#include "sani/engine/mono/texture2d_mono.hpp"
#include "sani/resource/texture2d.hpp"

#include <vector>

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(texture2d)

		struct Texture2DMono final {
			sani::resource::Texture2D*	nativeptr;
			MonoObject*					managedptr;

			Texture2DMono(sani::resource::Texture2D* const nativeptr, MonoObject* const managedptr) : nativeptr(nativeptr),
																									  managedptr(managedptr) {
			}
		};

		std::vector<Texture2DMono> instances;

		static Texture2DMono* getInstance(MonoObject* instance) {
			for (auto& texture2DMono : instances) if (texture2DMono.managedptr == instance) return &texture2DMono;

			return nullptr;
		}

		static void GetWidth(MonoObject* instance, int32* value) {
			*value = static_cast<int32>(getInstance(instance)->nativeptr->getWidth());
		}
		static void GetHeight(MonoObject* instance, int32* value) {
			*value = static_cast<int32>(getInstance(instance)->nativeptr->getHeight());
		}
		static void GetID(MonoObject* instance, int32* value) {
			*value = static_cast<int32>(getInstance(instance)->nativeptr->getID());
		}
		static void GetDisposed(MonoObject* instance, bool* value) {
			*value = getInstance(instance)->nativeptr->disposed();
		}

		MonoObject* createTexture2D() {
			const MonoClassDefinition texture2DDef("SaNi.Mono.Graphics", "Texture2D");

			MonoObject* instance = MONO_PROVIDER->createObject(&texture2DDef);
			MONO_PROVIDER->pin(instance);

			return instance;
		}

		MonoObject* getManagedPtr(const uint32 id) {
			for (auto& texture2DMono : instances) if (texture2DMono.nativeptr->getID() == id) return (MonoObject*)texture2DMono.managedptr;

			return nullptr;
		}
		sani::resource::Texture2D* getNativePtr(MonoObject* managedptr) {
			for (auto& texture2DMono : instances) if (texture2DMono.managedptr == managedptr) return texture2DMono.nativeptr;
			
			return nullptr;
		}

		void registerTexture2D(sani::resource::Texture2D* const nativeptr, MonoObject* const managedptr) {
			instances.push_back(Texture2DMono(nativeptr, managedptr));
		}
		void unregisterTexture2D(sani::resource::Texture2D* const nativeptr, MonoObject* const managedptr) {
			auto it = std::find_if(instances.begin(), instances.end(), [&managedptr](Texture2DMono& t) {
				return managedptr == t.managedptr;
			});

			instances.erase(it);
		}

		bool initialize() {
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Texture2D, GetWidth, GetWidth);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Texture2D, GetHeight, GetHeight);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Texture2D, GetID, GetID);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics, Texture2D, GetDisposed, GetDisposed);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}