#pragma once

#include "sani/types.hpp"

namespace sani {
	
	/*
		Collection of formatting functions that should be used
		with the loggers. Use these to keep the logging style
		unified.
	*/

	/// Formats the given error message.
	void formatError(const String& from, String& error);
	
	/// Formats the given warning message.
	void formatWarning(const String& from, String& warning);

	/// Formats the given info message.
	void formatInfo(const String& from, String& info);
}