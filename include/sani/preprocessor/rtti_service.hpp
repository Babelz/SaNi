#pragma once
#include "sani/engine/sani_engine.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/rtti/argument.hpp"
namespace se = sani::engine;
#define RTTI_DEFAULT_SERVICE_CTOR(p_class)                                                                    \
	db.types[typeof(p_class*).getID()].                                                                       \
addServiceConstructor<p_class*, se::SaNiEngine*, se::messages::DocumentMessage*>([](sani::rtti::Arguments& a){\
          auto engine = a[0].getValue<sani::engine::SaNiEngine*>();                                           \
          auto msg = a[1].getValue<sani::engine::messages::DocumentMessage*>();                               \
          engine->routeMessage(msg);                                                                          \
          sani::rtti::Object obj(static_cast<p_class*>(msg->getData()));                                      \
          engine->releaseMessage(msg);                                                                        \
          return obj;                                                                                         \
    });



