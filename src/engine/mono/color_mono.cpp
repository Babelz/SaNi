#include "sani/engine/mono/color_mono.hpp"
#include "sani/engine/mono/mono_include.hpp"

#include "sani/graphics/color.hpp"

namespace sani {

	namespace engine {
		
		namespace mono {
			
			namespace color {

				const MonoClassDefinition ClassDef("SaNi.Mono.Graphics", "Color");
				const MonoFieldDefinition RDef("r");
				const MonoFieldDefinition GDef("g");
				const MonoFieldDefinition BDef("b");
				const MonoFieldDefinition ADef("a");

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
				/*	MONO_PROVIDER->readField(from, &ClassDef, &RDef);
					MONO_PROVIDER->readField(from, &ClassDef, &GDef);
					MONO_PROVIDER->readField(from, &ClassDef, &BDef);
					MONO_PROVIDER->readField(from, &ClassDef, &ADef);
				*/}
				void copyData(graphics::Color* const from, MonoObject* to) {
					//MONO_PROVIDER->writeField(to, &ClassDef, &RDef, &from->r);
					//MONO_PROVIDER->writeField(to, &ClassDef, &GDef, &from->g);
					//MONO_PROVIDER->writeField(to, &ClassDef, &BDef, &from->b);
					//MONO_PROVIDER->writeField(to, &ClassDef, &ADef, &from->a);
				}
			}
		}
	}
}