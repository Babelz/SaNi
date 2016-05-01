#pragma once

#include "sani/engine/mono/shape_handler_mono.hpp"

namespace sani {

	namespace engine {

		namespace mono {
			
			// Lookup function.
			template<class T>
			static T* getInstance(MonoObject* object) {
				const uint32 ptr = *MONO_UNBOX(MONO_PROVIDER->readField(object, "ptr"), uint32);

				return reinterpret_cast<T*>(ptr);
			}

			// Border thickness.
			template<class T>
			static void GetBorderThickness(MonoObject* object, float32* value) {
				T* instance = getInstance(object);

				*value = instance->borderThickness;
			}
			template<class T>
			static void SetBorderThickness(MonoObject* object, float32 value) {
				T* instance = getInstance(object);

				instance->borderThickness = value;
			}

			// Fill.
			template<class T>
			static void GetFill(MonoObject* object, MonoObject* value) {
				
			}
			template<class T>
			static void SetFill(MonoObject* object, MonoObject value) {
			}

			// Border fill.
			template<class T>
			static void GetBorderFill(MonoObject* object, MonoObject* value) {
			}
			template<class T>
			static void SetBorderFill(MonoObject* object, MonoObject value) {
			}

			template<class T>
			void registerShapeMembers(std::vector<T*>* handles, MonoClassDefinition* classDef) {
			}
		}
	}
}