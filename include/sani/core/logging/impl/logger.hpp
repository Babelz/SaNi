#pragma once

#include "sani/core/logging/logger.hpp"

namespace sani {

	template<class T>
	Logger<T>::Logger(const String& name) : name(name) {
	}

	template<class T>
	const String& Logger<T>::getName() const {
		return name;
	}

	template<class T>
	void Logger<T>::log(const String& from, const LogLevel logLevel, const String& message) {
		switch (logLevel) {
		case LogLevel::Error:
			logError(from, message);
			break;		
		case LogLevel::Warning:
			logWarning(from, message);
			break;		
		case LogLevel::Info:
			logInfo(from, message);
			break;
		default:
			throw std::runtime_error("unsupported or invalid LogLevel type");
		}
	}
	
	/*
		Calls to child class.
	*/

	template<class T>
	void Logger<T>::logError(const String& from, const String& message) {
		static_cast<T*>(this)->logError(from, message);
	}
	template<class T>
	void Logger<T>::logWarning(const String& from, const String& message) {
		static_cast<T*>(this)->logWarning(from, message);
	}
	template<class T>
	void Logger<T>::logInfo(const String& from, const String& message) {
		static_cast<T*>(this)->logInfo(from, message);
	}
}