#pragma once

#include "sani/engine/mono/renderable_handler_mono.hpp"

namespace sani {

	namespace engine {

		namespace mono {

			template<class T>
			RenderableHandlerMono<T>::RenderableHandlerMono(HandleList* const handles, const MonoClassDefinition& classDef) : handles(handles) {
				// Lookup function.
				static const auto getInstance = [&handles](MonoObject* object) {
					const guint32 id = *MONO_UNBOX(MONO_PROVIDER->readField(instance, "id"), guint32);

					return handles->operator[](id);
				};

				// Transform.
				static const auto GetTransform = [&handles, getInstance](MonoObject* object, MonoObject** value) {
					T* const instance = getInstance(instance);

					MonoObject* transform = mono::transform::create(instance->transform.position,
																	instance->transform.scale,
																	instance->transform.origin,
																	instance->transform.rotation);

					value[0] = transform;
				};
				static const auto SetTransform = [&handles, getInstance](MonoObject* object, MonoObject* value) {
					T* const instance = getInstance(object);

					const math::Vec3f position = mono::transform::getPosition(value);
					const math::Vec3f scale = mono::transform::getScale(value);
					const math::Vec3f origin = mono::transform::getOrigin(value);
					const float32 rotation = mono::transform::getRotation(value);

					instance->transform.position = position;
					instance->transform.scale = scale;
					instance->transform.origin = origin;
					instance->transform.rotation = rotation;

					recomputeVertices(*instance);
					recomputeBounds(*instance);
				};

				const MonoFunctionDefinition getTransform("GetTransform", GetTransform, 1);
				const MonoFunctionDefinition getTransform("SetTransform", SetTransform, 1);
				MONO_PROVIDER->addInternalCall(&classDef, &getTransform)

				// Localbounds.
				const auto GetLocalBounds = [&handles, getInstance](MonoObject* object, MonoObject** value) {
				};
				const auto SetLocalBounds = [&handles, getInstance](MonoObject* object, MonoObject* value) {
				};

				// Globalbounds.
				const auto GetGlobalBounds = [&handles, getInstance](MonoObject* object, MonoObject** value) {
				};
				const auto SetGlobalBounds = [&handles, getInstance](MonoObject* object, MonoObject* value) {
				};

				// Texturesouce.
				const auto GetTextureSource = [&handles, getInstance](MonoObject* object, MonoObject** value) {
				};
				const auto SetTextureSource = [&handles, getInstance](MonoObject* object, MonoObject* value) {
				};

				// Texture.
				const auto GetTexture = [&handles, getInstance](MonoObject* object, MonoObject** value) {
				};
				const auto SetTexture = [&handles, getInstance](MonoObject* object, MonoObject* value) {
				};

				// Visible.
				const auto GetVisible = [&handles, getInstance](MonoObject* object, MonoObject** value) {
				};
				const auto SetVisible = [&handles, getInstance](MonoObject* object, MonoObject* value) {
				};
			}
		};
	}
}
