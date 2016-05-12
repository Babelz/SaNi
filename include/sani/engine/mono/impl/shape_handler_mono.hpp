#pragma once

#include "sani/engine/mono/shape_handler_mono.hpp"

namespace sani {

	namespace engine {

		namespace mono {
			
			// Border thickness.
			template<class T>
			static void GetBorderThickness(MonoObject* object, float32* value) {
				T* instance = getInstance<T>(object);

				*value = instance->borderThickness;
			}
			template<class T>
			static void SetBorderThickness(MonoObject* object, float32 value) {
				T* instance = getInstance<T>(object);

				instance->borderThickness = value;

				recomputeVertices(*instance);
				updateRenderData(*instance);
			}

			// Fill.
			template<class T>
			static void GetFill(MonoObject* object, MonoObject* value) {
				T* instance = getInstance<T>(object);

				MonoColor* color = reinterpret_cast<MonoColor*>(value);
				color->r = instance->fill.r;
				color->g = instance->fill.g;
				color->b = instance->fill.b;
				color->a = instance->fill.a;
			}
			template<class T>
			static void SetFill(MonoObject* object, MonoObject value) {
				T* instance = getInstance<T>(object);

				MonoColor* color = reinterpret_cast<MonoColor*>(&value);
				instance->fill.r = color->r;
				instance->fill.g = color->g;
				instance->fill.b = color->b;
				instance->fill.a = color->a;

				recomputeVertices(*instance);
				updateRenderData(*instance);
			}

			// Border fill.
			template<class T>
			static void GetBorderFill(MonoObject* object, MonoObject* value) {
				T* instance = getInstance<T>(object);

				MonoColor* color = reinterpret_cast<MonoColor*>(value);
				color->r = instance->borderFill.r;
				color->g = instance->borderFill.g;
				color->b = instance->borderFill.b;
				color->a = instance->borderFill.a;
			}
			template<class T>
			static void SetBorderFill(MonoObject* object, MonoObject value) {
				T* instance = getInstance<T>(object);

				MonoColor* color = reinterpret_cast<MonoColor*>(&value);
				instance->borderFill.r = color->r;
				instance->borderFill.g = color->g;
				instance->borderFill.b = color->b;
				instance->borderFill.a = color->a;

				recomputeVertices(*instance);
				updateRenderData(*instance);
			}

			template<class T>
			void registerShapeMembers(std::vector<T*>* handles, MonoClassDefinition classDef) {
				const auto BorderThicknessGetter = &GetBorderThickness<T>;
				const auto BorderThicknessSetter = &SetBorderThickness<T>;
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetBorderThickness, BorderThicknessGetter);
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetBorderThickness, BorderThicknessSetter);

				const auto FillGetter = &GetFill<T>;
				const auto FillSetter = &SetFill<T>;
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetFill, FillGetter);
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetFill, FillSetter);

				const auto BorderFillGetter = &GetBorderFill<T>;
				const auto BorderFillSetter = &SetBorderFill<T>;
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, GetBorderFill, BorderFillGetter);
				MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(classDef, SetBorderFill, BorderFillSetter);
			}
		}
	}
}