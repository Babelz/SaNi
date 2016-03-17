#pragma once

#include "sani/core/logging/log.hpp"

#define LOG_DEAD_LETTER(msg) FNCLOG_WRN(sani::log::OutFlags::All, "message was left unhandled"); msg->markHandled() 