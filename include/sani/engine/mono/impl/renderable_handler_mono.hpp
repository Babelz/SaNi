#pragma once

#include "sani/engine/mono/structs_mono.hpp"
#include "sani/engine/mono/renderable_handler_mono.hpp"
#include "sani/engine/mono/texture2d_mono.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			// Transform.
			template<class T>
			static void GetTransform(MonoObject* object, MonoObject* value) {
				T* instance = getInstance<T>(object);

				MonoTransform* transform = reinterpret_cast<MonoTransform*>(value);
				transform->px = instance->transform.position.x;
				transform->py = instance->transform.position.y;
				transform->pz = instance->transform.position.z;

				transform->sx = instance->transform.scale.x;
				transform->sy = instance->transform.scale.y;
				transform->sz = instance->transform.scale.z;

				transform->ox = instance->transform.origin.x;
				transform->oy = instance->transform.origin.y;
				transform->oz = instance->transform.origin.z;

				transform->r = instance->transform.rotation;
			};
			template<class T>
			static void SetTransform(MonoObject* object, MonoObject value) {
				T* instance = getInstance<T>(object);

				MonoTransform* transform = reinterpret_cast<MonoTransform*>(&value);
				instance->transform.position.x = transform->px;
				instance->transform.position.y = transform->py;
				instance->transform.position.z = transform->pz;

				instance->transform.scale.x = transform->sx;
				instance->transform.scale.y = transform->sy;
				instance->transform.scale.z = transform->sz;

				instance->transform.origin.x = transform->ox;
				instance->transform.origin.y = transform->oy;
				instance->transform.origin.z = transform->oz;

				instance->transform.rotation = transform->r;

				recomputeVertices(*instance);
			};
			
			// Localbounds.
			template<class T>
			static void GetLocalBounds(MonoObject* object, MonoObject* value) {
				T* instance = getInstance<T>(object);

				MonoRectf* rectf = reinterpret_cast<MonoRectf*>(value);
				rectf->x = instance->localBounds.x;
				rectf->y = instance->localBounds.y;
				rectf->w = instance->localBounds.w;
				rectf->h = instance->localBounds.h;
			};
			template<class T>
			static void SetLocalBounds(MonoObject* object, MonoObject value) {
				T* instance = getInstance<T>(object);

				MonoRectf* rectf = reinterpret_cast<MonoRectf*>(&value);
				instance->localBounds.x = rectf->x;
				instance->localBounds.y = rectf->y;
				instance->localBounds.w = rectf->w;
				instance->localBounds.h = rectf->h;

				recomputeBounds(*instance);
			};

			// Globalbounds.
			template<class T>
			static void GetGlobalBounds(MonoObject* object, MonoObject* value) {
				T* instance = getInstance<T>(object);

				MonoRectf* rectf = reinterpret_cast<MonoRectf*>(value);
				rectf->x = instance->globalBounds.x;
				rectf->y = instance->globalBounds.y;
				rectf->w = instance->globalBounds.w;
				rectf->h = instance->globalBounds.h;
			};

			// Texturesouce.
			template<class T>
			static void GetTextureSource(MonoObject* object, MonoObject* value) {
				T* instance = getInstance<T>(object);

				MonoRectf* rectf = reinterpret_cast<MonoRectf*>(&value);
				rectf->x = instance->textureSource.x;
				rectf->y = instance->textureSource.y;
				rectf->w = instance->textureSource.w;
				rectf->h = instance->textureSource.h;
			};
			template<class T>
			static void SetTextureSource(MonoObject* object, MonoObject value) {
				T* instance = getInstance<T>(object);

				MonoRectf* rectf = reinterpret_cast<MonoRectf*>(&value);
				instance->textureSource.x = rectf->x;
				instance->textureSource.y = rectf->y;
				instance->textureSource.w = rectf->w;
				instance->textureSource.h = rectf->h;
			};

			// Texture.
			template<class T>
			static void GetTexture(MonoObject* object, MonoObject** value) {
				T* instance = getInstance<T>(object);

				if (instance->texture == nullptr) return;

				MonoObject* managedPtr = texture2dmonomodule::getManagedPtr(instance->texture->getID());

				*value = managedPtr;
			};
			template<class T>
			static void SetTexture(MonoObject* object, MonoObject* value) {
				T* instance = getInstance<T>(object);

				if (value == nullptr) return;

				resource::Texture2D* texture = mono::texture2dmonomodule::getNativePtr(value);

				instance->texture = texture;

				updateRenderData(*instance);
			};

			// Visible.
			template<class T>
			static void GetVisible(MonoObject* object, int32* value) {
				T* instance = getInstance<T>(object);

				*value = instance->visible ? 1 : 0;
			};
			template<class T>
			static void SetVisible(MonoObject* object, int32 value) {
				T* instance = getInstance<T>(object);

				instance->visible = value ? true : false;
			};

			template<class T>
			void registerRenderableMembers(std::vector<T*>* handles, MonoClassDefinition classDef) {
				const auto TransformGetter = &GetTransform<T>;
				const auto TransformSetter = &SetTransform<T>;
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetTransform, TransformGetter);
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetTransform, TransformSetter);

				const auto LocalBoundsGetter = &GetLocalBounds<T>;
				const auto LocalBoundsSetter = &SetLocalBounds<T>;
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetLocalBounds, LocalBoundsGetter);
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetLocalBounds, LocalBoundsSetter);

				const auto GlobalBoundsGetter = &GetGlobalBounds<T>;
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetGlobalBounds, GlobalBoundsGetter);

				const auto TextureSourceGetter = &GetTextureSource<T>;
				const auto TextureSourceSetter = &SetTextureSource<T>;
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetTextureSource, TextureSourceGetter);
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetTextureSource, TextureSourceSetter);

				const auto TextureGetter = &GetTexture<T>;
				const auto TextureSetter = &SetTexture<T>;
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetTexture, TextureGetter);
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetTexture, TextureSetter);

				const auto VisibleGetter = &GetVisible<T>;
				const auto VisibleSetter = &SetVisible<T>;
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetVisible, VisibleGetter);
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetVisible, VisibleSetter);
			}
		}
	}
}