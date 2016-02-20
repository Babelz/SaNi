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

