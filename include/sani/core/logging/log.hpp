#pragma once

#include "sani/core/logging/out_flags.hpp"
#include "sani/core/logging/impl/log_impl.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_1(sani, LogBatcher);

/*
	Some helper macros that replace the from argument of the log functions
	to the current function name.
*/

#define FNCLOG_ERR(outFlags, message) log::error(outFlags, __FUNCTION___, message)
#define FNCLOG_WRN(outFlags, message) log::wraning(outFlags, __FUNCTION___, message)
#define FNCLOG_INF(outFlags, message) log::info(outFlags, __FUNCTION___, message)

/*
	Helper macros that do the same but replace the from argument with
	"[filename]@[function]".
*/

#define FLOG_ERR(outFlags, message) log::error(outFlags, __FILE__ + "@" + __FUNCTION__, message)
#define FLOG_WRN(outFlags, message) log::wraning(outFlags, __FILE__ + "@" + __FUNCTION__, message)
#define FLOG_INF(outFlags, message) log::info(outFlags, __FILE__ + "@" + __FUNCTION__, message)


namespace sani {

	template<class T>
	class Logger;

	namespace log {

		namespace {
			LogImpl impl;
		}

		void error(const OutFlags outFlags, const String& from, const String& message);
		void warning(const OutFlags outFlags, const String& from, const String& message);
		void info(const OutFlags outFlags, const String& from, const String& message);
		
		void batch(const OutFlags outFlags, LogBatcher& batcher);
	}
}