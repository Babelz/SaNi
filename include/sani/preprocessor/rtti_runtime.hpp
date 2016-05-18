#pragma once
#include "sani/rtti/type_database.hpp"
#include "sani/rtti/type_info.hpp"
#include "sani/engine/sani_engine.hpp"


#define RTTI_REGISTER_TYPE_VARIANT(type)                           \
{                                                                  \
	auto& db = sani::rtti::TypeDatabase::getInstance();            \
	auto id = db.registerType(#type);                              \
	sani::rtti::TypeInfo<type>::registerType(id, db.types[id], true);    \
}                                                                  \

#define RTTI_REGISTER_TYPE(type)                          \
	RTTI_REGISTER_TYPE_VARIANT(type)                               \

#define RTTI_PROPERTY(p_class, p_name, p_type, p_getter, p_setter)                   \
db.types[typeof(p_class).getID()].addField<p_class, p_type>(#p_name,                 \
	[](const sani::rtti::Object& instance) {                                         \
	    return instance.getValue<##p_class>().##p_getter();                          \
	},                                                                               \
	[](sani::rtti::Object& instance, const sani::rtti::Object& v) {                  \
	    instance.getValue<##p_class>().##p_setter(v.getValue<p_type>());             \
    });                  

#define RTTI_READONLY_PROPERTY(p_class, p_name, p_type, p_getter)                    \
	db.types[typeof(p_class).getID()].addField<p_class, p_type>(#p_name,             \
	[](const sani::rtti::Object& instance) {                                         \
	    return instance.getValue<##p_class>().##p_getter();                          \
	},                                                                               \
	nullptr);              

#define RTTI_PUBLIC_FIELD(p_class, p_name, p_type)                                   \
	db.types[typeof(p_class).getID()].addField<p_class, p_type>(#p_name,             \
	[](const sani::rtti::Object& instance) {                                         \
	    return instance.getValue<##p_class>().p_name;                                \
	},                                                                               \
	[](sani::rtti::Object& instance, const sani::rtti::Object& v) {                  \
	    instance.getValue<##p_class>().p_name = v.getValue<p_type>();                \
    });       

#define RTTI_PUBLIC_FIELD_PTR(p_class, p_name, p_type)                               \
	db.types[typeof(p_class*).getID()].addField<p_class*, p_type>(#p_name,           \
	[](const sani::rtti::Object& instance) {                                         \
	    return instance.getValue<##p_class*>()->p_name;                              \
    },                                                                               \
	[](sani::rtti::Object& instance, const sani::rtti::Object& v) {                  \
	    instance.getValue<##p_class*>()->p_name = v.getValue<p_type>();              \
    });      

#define RTTI_DECLARE_BASECLASSES(p_class, ...)                                       \
	db.types[typeof(p_class).getID()].loadBaseClasses(db, typeof(p_class).getID(),   \
	{ ##__VA_ARGS__ });

#define RTTI_CONSTRUCTOR_BODY(p_class, ...)                                                 \
	db.types[typeof(p_class).getID()].addConstructor<##p_class, ##__VA_ARGS__>([](sani::rtti::Arguments& args){

#define RTTI_CONSTRUCTOR_END }, false);

#define RTTI_DYNAMIC_CONSTRUCTOR_END }, true);

#define RTTI_DEFAULT_CTOR(p_class)                                                    \
	db.types[typeof(p_class).getID()].addConstructor<##p_class>([](sani::rtti::Arguments&){ \
              return p_class();                                                             \
	}, false);

#define RTTI_DEFAULT_DYNAMIC_CTOR(p_class)                                                    \
	db.types[typeof(p_class).getID()].addConstructor<p_class>([](sani::rtti::Arguments&){ \
              return new p_class();                                                           \
	}, true);

