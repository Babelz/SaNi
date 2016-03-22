#include "sani/core/logging/logging_helpers.hpp"
#include "sani/platform/file/file_stream.hpp"
#include "sani/core/logging/file_logger.hpp"
#include "sani/debug.hpp"

namespace sani {

	FileLogger::FileLogger(const String& path) : Logger<FileLogger>("file logger"),
												 stream(nullptr),
												 path(path) {
		SANI_ASSERT(!path.empty());

		if (!fileSystem.openFile(path, io::Filemode::Truncate, &stream)) std::abort();
	}

	void FileLogger::internalLog(const String& from, const String& message, const LogLevel level) {
		SANI_ASSERT(stream != nullptr);

		String out;
		formatOut(out, from, message, level);

		const char* cstr			= out.c_str();
		const unsigned char* ucstr	= reinterpret_cast<const unsigned char*>(cstr);
		
		stream->write(ucstr, static_cast<uint32>(out.size()));
	}

	void FileLogger::logError(const String& from, const String& message) {
		internalLog(from, message, LogLevel::Error);
	}
	void FileLogger::logWarning(const String& from, const String& message) {
		internalLog(from, message, LogLevel::Warning);
	}
	void FileLogger::logInfo(const String& from, const String& message) {
		internalLog(from, message, LogLevel::Info);
	}

	FileLogger::~FileLogger() {
		if (stream != nullptr) stream->flush();
		
		fileSystem.closeFile(path);
	}
}