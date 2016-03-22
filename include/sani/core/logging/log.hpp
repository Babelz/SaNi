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

#define FNCLOG_ERR(outFlags, message) sani::log::__privns__::error(outFlags, __FUNCTION__, message)
#define FNCLOG_WRN(outFlags, message) sani::log::__privns__::warning(outFlags, __FUNCTION__, message)
#define FNCLOG_INF(outFlags, message) sani::log::__privns__::info(outFlags, __FUNCTION__, message)

/*
	Helper macros that do the same but replace the from argument with
	"[filename]@[function]".
*/

#define FLOG_ERR(outFlags, message) sani::log::__privns__::error(outFlags, __FILE__  "@" __FUNCTION__, message)
#define FLOG_WRN(outFlags, message) sani::log::__privns__::warning(outFlags, __FILE__  "@"  __FUNCTION__, message)
#define FLOG_INF(outFlags, message) sani::log::__privns__::info(outFlags, __FILE__  "@"  __FUNCTION__, message)

/*
	Raw logging macros.
*/

#define RLOG_ERR(outFlags, from, message) sani::log::__privns__::error(outFlags, from, message)
#define RLOG_WRN(outFlags, from, message) sani::log::__privns__::warning(outFlags, from, message)
#define RLOG_INF(outFlags, from, message) sani::log::__privns__::info(outFlags, from, message)

namespace sani {

	template<class T>
	class Logger;

	namespace log {

		namespace {

			LogImpl impl;
		}

		namespace __privns__ {

			void error(const OutFlags outFlags, const String& from, const String& message);
			void warning(const OutFlags outFlags, const String& from, const String& message);
			void info(const OutFlags outFlags, const String& from, const String& message);
		}

		void batch(const OutFlags outFlags, LogBatcher& batcher);
	}
}