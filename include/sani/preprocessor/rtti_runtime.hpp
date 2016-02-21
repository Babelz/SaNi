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


#define DECLARE_SERIALIZABLE									   \
	public:                                                        \
	sani::rtti::Type getType() const override {                    \
	    return sani::rtti::Type(                                   \
               sani::rtti::TypeInfo<                               \
                      sani::rtti::PureType<decltype(*this)> >::id);         \
	}                                                              \
	sani::rtti::Serializable* clone() const override {             \
	       throw std::logic_error("not impl");                     \
    }                                                              \
	private: