#pragma once

#include "sani/engine/sani_engine.hpp"
#include "sani/engine/mono/mono_include.hpp"
#include "sani/types.hpp"

#define MONO_UNBOX(__val__, __type__) (__type__*)mono_object_unbox(__val__)

#define MONO_MODULE_DEF(name) namespace sani { \
								  namespace engine { \
									class SaNiEngine; \
										namespace mono { \
										  namespace name##monomodule {	\
												extern const char* const ModuleName; \
												extern sani::engine::SaNiEngine* engine; \
												bool initialize(); \
												} \
											} \
										} \
									} \

#define MONO_MODULE_DEF_BEGIN(name) namespace sani { \
										namespace engine { \
											class SaNiEngine; \
											namespace mono {  \
											namespace name##monomodule {	\
												extern const char* const ModuleName; \
												extern sani::engine::SaNiEngine* engine; \
												bool initialize(); \

#define MONO_MODULE_DEF_END		} \
							} \
						} \
					} \

#define MONO_MODULE_IMPL(name) namespace mono { \
								namespace name##monomodule { \
									const char* const ModuleName = #name; \
									sani::engine::SaNiEngine* engine = nullptr; \
									using namespace sani::engine::mono; \

#define MONO_MODULE_IMPL_END	} \
							} \

#define MONO_PROVIDER sani::engine::mono::MonoRuntime::instance().provider()
#define MONO_RUNTIME sani::engine::mono::MonoRuntime::instance()

#define MONO_REGISTER_MODULE(__name__)  mono::__name__##monomodule::engine = this; \
									    if (!mono::__name__##monomodule::initialize()) return false \


#define MONO_REGISTER_KNOWN_FUNCTION(__ns__, __class__, __func__, ptr)	{ \
																			const MonoClassDefinition _classDef(#__ns__, #__class__); \
																			const MonoFunctionDefinition _funcDef(#__func__, ptr); \
																			MONO_PROVIDER->addInternalCall(&_classDef, &_funcDef); \
																		} \

#define MONO_REGISTER_KNOWN_FUNCTION_FROM_DEF(__classdef__, __func__, ptr)	{ \
																				const MonoFunctionDefinition _funcDef(#__func__, ptr); \
																				MONO_PROVIDER->addInternalCall(&__classdef__, &_funcDef); \
																		    } \


namespace sani {

	namespace engine {

		namespace mono {

			struct MonoClassDefinition final {
				const char* const ns;
				const char* const name;

				MonoClassDefinition(const char* const ns, const char* const name);
				MonoClassDefinition();

				~MonoClassDefinition() = default;

				MonoClassDefinition operator = (const MonoClassDefinition& classDef);
			};

			struct MonoFunctionDefinition final {
				const char* const name;
				const void* const ptr;
				const uint32 argc;

				MonoFunctionDefinition(const char* const name, const void* const ptr, const uint32 argc = 0);

				~MonoFunctionDefinition() = default;
			};

			/// Returns the native instance that the managed object 
			/// is associated with. Requires that the managed object
			/// has a field called ptr of type uint containing the address of the
			/// native instance.
 			template<typename T>
			T* getInstance(MonoObject* object) {
				const uint32 ptr = *MONO_UNBOX(MONO_PROVIDER->readField(object, "ptr"), uint32);

				return reinterpret_cast<T*>(ptr);
			}
		}
	}
}