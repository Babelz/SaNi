#pragma once

#include "sani/engine/mono/mono_define.hpp"

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <mono\metadata\object.h>

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D)

MONO_MODULE_DEF_BEGIN(texture2d)

MonoObject* createTexture2D();

MonoObject* getManagedPtr(const uint32 id);
sani::resource::Texture2D* getNativePtr(MonoString* managedptr);

void registerTexture2D(sani::resource::Texture2D* const nativeptr, MonoObject* const managedptr);
void unregisterTexture2D(sani::resource::Texture2D* const nativeptr, MonoObject* const managedptr);

MONO_MODULE_DEF_END