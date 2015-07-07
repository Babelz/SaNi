#pragma once

#include "sani/platform/platform_config.hpp"


/* Win32 */
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

/// Calls Win32 GetLastError and uses CAssert to deal with assertions.
#define WIN32_ASSERT() assert(GetLastError() == 0);

/// Calls Win32 GetLastError and uses Win32 message box to show user defined
/// error message if assertion failed.
#define WIN32_REQUIRE(hwnd, text) if (GetLastError() != 0) MessageBox(hwnd, text, L"Assertion failure!", MB_OK);

#endif

