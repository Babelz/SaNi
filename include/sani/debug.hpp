#pragma once

#include "sani/platform/platform_config.hpp"
#include <cassert>

#include "sani/platform.hpp"
#define __SANI_INFO__(message) String(message +											\
							          " - @File: " + __FILE__ +							\
							          " @Function: " + __FUNCTION__	+					\
								      " @Line: " + std::to_string(__LINE__))			\

// Generates message with no category.
#define SANI_MESSAGE(message)			__SANI_INFO__(String(message))
// Generates a common message.
#define SANI_GENERIC_MESSAGE(message)	__SANI_INFO__(String("Message: ") + String(message))
// Generates a warning message.
#define SANI_WARNING_MESSAGE(message)	__SANI_INFO__(String("Warning: ") + String(message))
// Generates a error message.
#define SANI_ERROR_MESSAGE(message)		__SANI_INFO__(String("Error: ") + String(message))

#define SANI_ASSERT(condition) assert((condition))

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

/// Calls Win32 GetLastError and uses CAssert to deal with assertions.
#define WIN32_ASSERT() //assert(GetLastError() == 0)

/// Calls Win32 GetLastError and uses Win32 message box to show user defined
/// error message if assertion failed.
#define WIN32_REQUIRE(hwnd, text) if (GetLastError() != 0) MessageBox(hwnd, text, L"Assertion failure!", MB_OK)

#endif