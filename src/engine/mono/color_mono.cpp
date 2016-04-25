#include "sani/engine/mono/color_mono.hpp"
#include "sani/engine/mono/mono_include.hpp"

#include "sani/graphics/color.hpp"

namespace sani {

	namespace engine {
		
		namespace mono {
			
			namespace color {

				const MonoClassDefinition ClassDef("SaNi.Mono.Graphics", "Color");
				const char* const FieldR = "r";
				const char* const FieldG = "g";
				const char* const FieldB = "b";
				const char* const FieldA = "a";

				MonoObject* create(float32 r, float32 g, float32 b, float32 a) {
					const uint32 argc = 4;

					void* args[argc] = {
						&r,
						&g,
						&b,
						&a
					};

					return MONO_PROVIDER->createObject(&ClassDef, args, argc);
				}

				void copyData(MonoObject* from, graphics::Color* const to) {
					to->r = *MONO_UNBOX(MONO_PROVIDER->readField(from, FieldR), float32);
					to->g = *MONO_UNBOX(MONO_PROVIDER->readField(from, FieldG), float32);
					to->b = *MONO_UNBOX(MONO_PROVIDER->readField(from, FieldB), float32);
					to->a = *MONO_UNBOX(MONO_PROVIDER->readField(from, FieldA), float32);
				}
				void copyData(graphics::Color* const from, MonoObject* to) {
					MONO_PROVIDER->writeField(to, FieldR, &from->r);
					MONO_PROVIDER->writeField(to, FieldG, &from->g);
					MONO_PROVIDER->writeField(to, FieldB, &from->b);
					MONO_PROVIDER->writeField(to, FieldA, &from->a);
				}
			}
		}
	}
}