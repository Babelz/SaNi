#pragma once
#include "sani/rtti/type_database.hpp"
#include "sani/rtti/type_info.hpp"

#define RTTI_REGISTER_TYPE_VARIANT(type)                           \
{                                                                  \
	auto& db = sani::rtti::TypeDatabase::getInstance();            \
	auto id = db.registerType(#type);                              \
	sani::rtti::TypeInfo<type>::registerType(id, db.types[id], true);    \
}                                                                  \

#define RTTI_REGISTER_TYPE(type)                                   \
	RTTI_REGISTER_TYPE_VARIANT(type)                               \
	RTTI_REGISTER_TYPE_VARIANT(type*)                              \
	RTTI_REGISTER_TYPE_VARIANT(const type*)                        


#define DECLARE_REFLECTABLE						   			       \
	public:                                                        \
	sani::rtti::Type getType() const override {                    \
	    return sani::rtti::Type(                                   \
               sani::rtti::TypeInfo<                               \
                      sani::rtti::PureType<decltype(*this)> >::id);         \
	}                                                              \
	sani::rtti::Reflectable* clone() const override {             \
	       throw std::logic_error("not impl");                     \
    }                                                              \
	private:

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

#define RTTI_DECLARE_BASECLASSES(p_class, ...)                                       \
	db.types[typeof(p_class).getID()].loadBaseClasses(db, typeof(p_class).getID(),   \
	{ ##__VA_ARGS__ });