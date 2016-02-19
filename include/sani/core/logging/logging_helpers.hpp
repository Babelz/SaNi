#pragma once

#include "sani/types.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_ENUM_CLASS_1(sani, LogLevel);

namespace sani {
	
	/*
		Collection of formatting functions that should be used
		with the loggers. Use these to keep the logging style
		unified.
	*/

	void formatOut(String& out, const String& from, const String& message, const LogLevel level);

	/// Formats the given error message.
	void formatError(String& out, const String& from, const String& error);
	
	/// Formats the given warning message.
	void formatWarning(String& out, const String& from, const String& warning);

	/// Formats the given info message.
	void formatInfo(String& out, const String& from, const String& info);
}