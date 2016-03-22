#pragma once

// All platforms we are supporting
#define SANI_PLATFORM_UNKOWN		0
// Desktop
#define SANI_PLATFORM_WINDOWS		1
#define SANI_PLATFORM_LINUX			2
#define SANI_PLATFORM_MAC			3

// Mobile
/*#define SANI_PLATFORM_ANDROID		4
#define SANI_PLATFORM_WP8			5
#define SANI_PLATFORM_IOS			6
// For future..
#define SANI_PLATFORM_EMSCRIPTEN	7
#define SANI_PLATFORM_PS4			8
#define SANI_PLATFORM_XBOX_ONE		9*/

// Lets figure out our platform from compiler environment variable
#define SANI_TARGET_PLATFORM		SANI_PLATFORM_UNKOWN

// win32
#if (defined(_WIN32) || defined(_WIN64))
#undef SANI_TARGET_PLATFORM
#define SANI_TARGET_PLATFORM SANI_PLATFORM_WINDOWS
#endif

// Linux
#if defined(__linux__) && !defined(__APPLE__)
#undef SANI_TARGET_PLATFORM
#define SANI_TARGET_PLATFORM SANI_PLATFORM_LINUX
#endif

// Mac and iOS
#if defined(__APPLE__)
#include "TargetConditionals.h"
#undef  SANI_TARGET_PLATFORM

//#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
//#define SANI_TARGET_PLATFORM         SANI_PLATFORM_IOS
#if defined(TARGET_OS_MAC)
#define SANI_TARGET_PLATFORM		SANI_PLATFORM_MAC
#endif
#endif


// Android
#if defined(ANDROID)
//#undef  SANI_TARGET_PLATFORM
//#define SANI_TARGET_PLATFORM         SANI_PLATFORM_ANDROID
#endif

// WP8 
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
//#undef  SANI_TARGET_PLATFORM
//#define SANI_TARGET_PLATFORM         SANI_PLATFORM_WP8
#endif*/

#define SANI_ARCH_UNKNOWN     0
#define SANI_ARCH_X86         1
#define SANI_ARCH_X64         2
#define SANI_TARGET_ARCH      SANI_ARCH_UNKNOWN

#if defined(__x86_64__)    || \
	defined(_M_X64)        || \
	defined(__aarch64__)   || \
	defined(__64BIT__)     || \
	defined(__mips64)      || \
	defined(__powerpc64__) || \
	defined(__ppc64__)
#undef SANI_TARGET_ARCH
#define SANI_TARGET_ARCH     SANI_ARCH_X64
#else
#undef SANI_TARGET_ARCH
#define SANI_TARGET_ARCH     SANI_ARCH_X86
#endif


#define SANI_DESKTOP         (SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS \
                           || SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX \
						   || SANI_TARGET_PLATFORM == SANI_PLATFORM_MAC)
#define SANI_MOBILE          0
#define SANI_CONSOLE         0