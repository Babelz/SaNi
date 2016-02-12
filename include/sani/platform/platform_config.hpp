#pragma once

// All platforms we are supporting
#define SANI_PLATFORM_UNKOWN		0
// Desktop
#define SANI_PLATFORM_WIN32			1
#define SANI_PLATFORM_LINUX			2
#define SANI_PLATFORM_MAC			3
// Mobile
#define SANI_PLATFORM_ANDROID		4
#define SANI_PLATFORM_WP8			5
#define SANI_PLATFORM_IOS			6
// For future..
#define SANI_PLATFORM_EMSCRIPTEN	7
#define SANI_PLATFORM_PS4			8
#define SANI_PLATFORM_XBOX_ONE		9

// Lets figure out our platform from compiler environment variable
#define SANI_TARGET_PLATFORM		SANI_PLATFORM_UNKOWN

// win32
#if ((defined(__WIN32__) || defined(_WIN32)))
#undef SANI_TARGET_PLATFORM
#define SANI_TARGET_PLATFORM SANI_PLATFORM_WIN32
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

#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
#define SANI_TARGET_PLATFORM         SANI_PLATFORM_IOS
#elif defined(TARGET_OS_MAC)
#define SANI_TARGET_PLATFORM		SANI_PLATFORM_MAC
#else
#error "Don't know if it's Mac, iPhone or iPad"
#endif
#endif


// Android
#if defined(ANDROID)
#undef  SANI_TARGET_PLATFORM
#define SANI_TARGET_PLATFORM         SANI_PLATFORM_ANDROID
#endif

// WP8 
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
#undef  SANI_TARGET_PLATFORM
#define SANI_TARGET_PLATFORM         SANI_PLATFORM_WP8
#endif

// Check if we got our platform
#if (SANI_TARGET_PLATFORM == SANI_PLATFORM_UNKOWN)
#error "Can not recognize platform"
#endif