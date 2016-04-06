#pragma once

#define MONO_MODULE_DEF(name) class SaNiEngine; \
							  namespace name##monomodule {	\
									namespace { \
										const char* const ModuleName = #name; \
										sani::engine::SaNiEngine* engine = nullptr; \
									} \
									void initialize(); \
							  } \

#define MONO_MODULE_IMPL(name) namespace name##monomodule { \

#define MONO_MODULE_INITIALIZER void initialize() \

#define MONO_MODULE_IMPL_END } \

#define MONO_PROVIDER sani::engine::MonoRuntime::instance().provider()
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
	
	const void* const ptr;

	MonoFunctionDefinition(const char* const name, const char* const signature, const void* const ptr) : name(name),
																										 signature(signature),
																										 ptr(ptr) {
	}

	~MonoFunctionDefinition() = default;
};

#define MONO_DEFINE_CLASS(__namespace__, __class__) const MonoClassDefinition __class__##Def(#__namespace__, #__class__); \
													if (!MONO_PROVIDER->classExists(&__class__##Def)) { \
														FLOG_ERR(log::OutFlags::All, "could not register mono class"); \
														return; \
													} else FLOG_INF(log::OutFlags::All, "registered mono class") \
													 

#define MONO_DEFINE_FUNCTION(__name__, __signature__) const MonoFunctionDefinition __name__##Def(#__name__, #__signature__, __name__##Impl)

#define MONO_FUNCTION_IMPL(__name__) __name__##Impl

#define MONO_REGISTER_MODULE(__name__, __engine__)  __name__##monomodule::engine = __engine__; \
												    __name__##monomodule::initialize()

