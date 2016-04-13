#pragma once

#include "sani/core/utils/string_utils.hpp"

#define NO_ARGS "NO_ARGS"

#define MONO_MODULE_DEF(name) namespace sani { \
								  namespace engine { \
									  class SaNiEngine; \
									  namespace name##monomodule {	\
											extern const char* const ModuleName; \
											extern sani::engine::SaNiEngine* engine; \
											bool initialize(); \
									  } \
								  } \
							  } \

#define MONO_MODULE_DEF_BEGIN(name) namespace sani { \
										namespace engine { \
											class SaNiEngine; \
											namespace name##monomodule {	\
												extern const char* const ModuleName; \
												extern sani::engine::SaNiEngine* engine; \
												bool initialize(); \

#define MONO_MODULE_DEF_END	} } } \ 

#define MONO_MODULE_IMPL(name) namespace name##monomodule { \
									const char* const ModuleName = #name; \
									sani::engine::SaNiEngine* engine = nullptr; \

#define MONO_MODULE_IMPL_END } \

#define MONO_PROVIDER sani::engine::MonoRuntime::instance().provider()
#define MONO_DOMAIN sani::engine::MonoRuntime::instance().domain()
#define MONO_RUNTIME sani::engine::MonoRuntime::instance()

struct MonoClassDefinition final {
	const char* const ns;
	const char* const name;

	MonoClassDefinition(const char* const ns, const char* const name) : ns(ns), 
																	    name(name) {
	}

	~MonoClassDefinition() = default;
};

struct MonoFunctionDefinition final {
	const char* const name;
	const char* const signature;
	uint32 argsc;
	
	const void* const ptr;

	MonoFunctionDefinition(const char* const name, const char* const signature, const void* const ptr) : name(name),
																										 signature(signature),
																										 ptr(ptr),
																										 argsc(0) {
		if (strlen(signature) != 0 && signature != NO_ARGS) {
			const auto commas = sani::utils::count(signature, ',');
			
			argsc = commas + 1;
		}
	}

	~MonoFunctionDefinition() = default;
};

#define MONO_DEFINE_CLASS(__namespace__, __class__) const MonoClassDefinition __class__##Def(#__namespace__, #__class__); \
													if (!MONO_PROVIDER->classExists(&__class__##Def)) { \
														FNCLOG_ERR(log::OutFlags::All, "could not register mono class, class not found"); \
														return false; \
													} else FNCLOG_INF(log::OutFlags::All, "registering mono class") \
													 

#define MONO_DEFINE_FUNCTION(__name__, __signature__) const MonoFunctionDefinition __name__##Def(#__name__, #__signature__, __name__##Impl); \

#define MONO_REGISTER_FUNCTION(__function__, __class__) if (!MONO_PROVIDER->functionExists(&__class__##Def, &__function__##Def)) { \
															FNCLOG_ERR(log::OutFlags::All, "could not register function, member not found"); \
															return false; \
														} else { FNCLOG_INF(log::OutFlags::All, "registering function"); MONO_PROVIDER->addInternalCall(&__class__##Def, &__function__##Def); }\

#define MONO_FUNCTION_IMPL(__name__) __name__##Impl

#define MONO_REGISTER_MODULE(__name__)  __name__##monomodule::engine = this; \
									    if (!__name__##monomodule::initialize()) return false

#define MONO_REGISTER_FUNCTION_IF_IMPL_FOUND(__ns__, __class__, __func__, __signature__, ptr)	{ \
																									const MonoClassDefinition _classDef(#__ns__, #__class__); \
																									const MonoFunctionDefinition _funcDef(#__func__, #__signature__, ptr); \
																									if (MONO_PROVIDER->functionExists(&_classDef, &_funcDef)) MONO_PROVIDER->addInternalCall(&_classDef, &_funcDef); \
																								} \


#define MONO_REGISTER_KNOWN_FUNCTION(__ns__, __class__, __func__, __signature__, ptr)	{ \
																									const MonoClassDefinition _classDef(#__ns__, #__class__); \
																									const MonoFunctionDefinition _funcDef(#__func__, #__signature__, ptr); \
																									MONO_PROVIDER->addInternalCall(&_classDef, &_funcDef); \
																						} \



