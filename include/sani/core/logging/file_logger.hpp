#pragma once

#include "sani/platform/file/file_system.hpp"
#include "sani/core/logging/logger.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, io, FileStream);

namespace sani {

	class FileLogger final : public Logger<FileLogger> {
	private:
		// Private file system instance and stream pointer
		// to the current file stream.
		const String path;

		io::FileSystem fileSystem;
		io::FileStream* stream;
		
		void internalLog(const String& from, const String& message, const LogLevel level);
	public:
		FileLogger(const String& path);

		void logError(const String& from, const String& message);
		void logWarning(const String& from, const String& message);
		void logInfo(const String& from, const String& message);

		virtual ~FileLogger();
	};
}