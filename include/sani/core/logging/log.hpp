#pragma once

#include "sani/core/logging/out_flags.hpp"
#include "sani/core/logging/impl/log_impl.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_1(sani, LogBatcher);

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