#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_1(sani, LogBatcher);

namespace sani {

	template<class T>
	class Logger;

	namespace log {
		struct Impl;

		namespace {
			const uint16 OutStreamsCount = 2;
			const uint16 OutFlagsNull = 0;

			Impl* impl;
		}

		const uint16 OutFlagsConsole = 1;
		const uint16 OutFlagsFile    = 2;
		const uint16 OutFlagsAll	 = OutFlagsConsole & OutFlagsFile;
		
		void initialize();
		void deinitialize();

		void error(const uint16 outFlags, const String& from, const String& message);
		void warning(const uint16 outFlags, const String& from, const String& message);
		void info(const uint16 outFlags, const String& from, const String& message);
		
		void batch(const uint16 outFlags, LogBatcher& batcher);
	}
}