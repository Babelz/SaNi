#pragma once

#include "sani/core/utils/string_utils.hpp"

#include <mono/metadata/object.h>
#include <functional>

#define NO_ARGS "NO_ARGS"

struct MonoFieldDefinition final {
	const char* const name;

	MonoFieldDefinition(const char* const name) : name(name) {
	}

	~MonoFieldDefinition() = default;
};

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
	const void* const ptr;
	const uint32 argc;

	MonoFunctionDefinition(const char* const name, const void* const ptr, const uint32 argc = 0) : name(name),
																								   ptr(ptr),
																							       argc(argc) {
	}

	~MonoFunctionDefinition() = default;
};

template<typename T>
using MonoGetter = std::function<T(MonoString*)>;

template<typename T>
using MonoSetter = std::function<void(MonoString*, T)>;

const uint32 PropsNull	 = 0;
const uint32 PropsGet	 = 1;
const uint32 PropsSet	 = 2;
const uint32 PropsGetSet = 3;

template<typename T>
struct MonoPropertyDefinition final {
	const uint32 settings   { PropsNull };
	const char* const name;

	MonoGetter<T> get;
	MonoSetter<T> set;

	MonoPropertyDefinition(const char* const name, const uint32 settings) : name(name),
																		    settings(settings) {
	}

	operator bool() const {
		const bool hasGetter = get ? true : false;
		const bool hasSetter = set ? true : false;
		
		if		(settings == PropsNull)	  return false;
		else if (settings == PropsGetSet) return hasGetter && hasSetter;
		else if (settings == PropsGet)	  return hasGetter;
		else if (settings == PropsSet)	  return hasSetter;

		// No access.
		return false;
	}
};

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

#define MONO_MODULE_DEF_END	} \
						} \
					} \

#define MONO_MODULE_IMPL(name) namespace name##monomodule { \
									const char* const ModuleName = #name; \
									sani::engine::SaNiEngine* engine = nullptr; \

#define MONO_MODULE_IMPL_END } \

#define MONO_PROVIDER sani::engine::MonoRuntime::instance().provider()
#define MONO_DOMAIN sani::engine::MonoRuntime::instance().domain()
#define MONO_RUNTIME sani::engine::MonoRuntime::instance()

#define MONO_DEFINE_CLASS(__namespace__, __class__) const MonoClassDefinition __class__##Def(#__namespace__, #__class__); \
													if (!MONO_PROVIDER->classExists(&__class__##Def)) { \
														FNCLOG_ERR(log::OutFlags::All, "could not register mono class, class not found"); \
														return false; \
													} else FNCLOG_INF(log::OutFlags::All, "registering mono class") \
													 

#define MONO_DEFINE_FUNCTION(__name__) const MonoFunctionDefinition __name__##Def(#__name__, __name__##Impl); \

#define MONO_REGISTER_FUNCTION(__function__, __class__) if (!MONO_PROVIDER->functionExists(&__class__##Def, &__function__##Def)) { \
															FNCLOG_ERR(log::OutFlags::All, "could not register function, member not found"); \
															return false; \
														} else { FNCLOG_INF(log::OutFlags::All, "registering function"); MONO_PROVIDER->addInternalCall(&__class__##Def, &__function__##Def); }\

#define MONO_FUNCTION_IMPL(__name__) __name__##Impl

#define MONO_REGISTER_MODULE(__name__)  __name__##monomodule::engine = this; \
									    if (!__name__##monomodule::initialize()) return false

#define MONO_REGISTER_FUNCTION_IF_IMPL_FOUND(__ns__, __class__, __func__, ptr)	{ \
																									const MonoClassDefinition _classDef(#__ns__, #__class__); \
																									const MonoFunctionDefinition _funcDef(#__func__, ptr); \
																									if (MONO_PROVIDER->functionExists(&_classDef, &_funcDef)) MONO_PROVIDER->addInternalCall(&_classDef, &_funcDef); \
																								} \


#define MONO_REGISTER_KNOWN_FUNCTION(__ns__, __class__, __func__, ptr)	{ \
																									const MonoClassDefinition _classDef(#__ns__, #__class__); \
																									const MonoFunctionDefinition _funcDef(#__func__, ptr); \
																									MONO_PROVIDER->addInternalCall(&_classDef, &_funcDef); \
																						} \

#define MONO_REGISTER_GETTER(__ns__, __class__, __pdef__) if (__pdef__.get) {\
															String fname("get_"); \
															fname = fname.append(__pdef__.name); \
															const MonoClassDefinition _classDef(__ns__, __class__); \
															const MonoFunctionDefinition _getDef(fname.c_str(), (void*)&__pdef__.get); \
															MONO_PROVIDER->addInternalCall(&_classDef, &_getDef); \
														} \


#define MONO_REGISTER_SETTER(__ns__, __class__, __pdef__) if (__pdef__.set) {\
																			String fname("set_"); \
																			fname = fname.append(__pdef__.name); \
																			const MonoClassDefinition _classDef(__ns__, __class__); \
																			const MonoFunctionDefinition _setDef(fname.c_str(), (void*)&__pdef__.set); \
																			MONO_PROVIDER->addInternalCall(&_classDef, &_setDef); \
																		 } \

#define MONO_REGISTER_PROPERTY(__ns__, __class__, __pdef__) MONO_REGISTER_GETTER(__ns__, __class__, __pdef__) \
															MONO_REGISTER_SETTER(__ns__, __class__, __pdef__) \

#define MONO_BASE_DEF_CHECK_FOR_NULL(__pname__, __def__) if (!__def__.__pname__) { FNCLOG_ERR(log::OutFlags::All, String(#__pname__) + " can't be null!"); return false; }