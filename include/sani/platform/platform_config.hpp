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

/************************************************************************/
/*                TODO THESE NEEDS TO BE TESTED!!!!!!!                  */
/************************************************************************/

// win32
// http://stackoverflow.com/questions/430424/are-there-any-macros-to-determine-if-my-code-is-being-compiled-to-windows
#if ((defined(__WIN32__) || defined(_WIN32)))
#undef SANI_TARGET_PLATFORM
#define SANI_TARGET_PLATFORM SANI_PLATFORM_WIN32
#endif

// Linux
// http://stackoverflow.com/questions/4605842/how-to-identify-platform-compiler-from-preprocessor-macros
// Don't know if apple defines __linux__
// TODO: maybe we should define LINUX or _LINUX in premake4?
#if defined(__linux__) && !defined(__APPLE__)
#undef SANI_TARGET_PLATFORM
#define SANI_TARGET_PLATFORM SANI_PLATFORM_LINUX
#endif

// Mac and iOS
/*
From stackoverflow: 
__APPLE__ is set for both OS X and iOS. 
You can #include <TargetConditionals.h> inside #ifdef __APPLE__, which then gives you a TARGET_OS_IPHONE #define
*/
#if defined(__APPLE__)
#include "TargetConditionals.h"
#undef  SANI_TARGET_PLATFORM

#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
#define SANI_TARGET_PLATFORM         SANI_PLATFORM_IOS
#elif defined(TARGET_OS_MAC)
#define SANI_TARGET_PLATFORM		SANI_PLATFORM_MAC
#else
#error "Don't know if it's Mac or iPhone/Pad"
#endif
#endif


// Android
// TODO: I guess we need to change our build system maybe?
// http://stackoverflow.com/questions/6374523/how-to-detect-compilation-by-android-ndk-in-a-c-c-file
#if defined(ANDROID)
#undef  SANI_TARGET_PLATFORM
#define SANI_TARGET_PLATFORM         SANI_PLATFORM_ANDROID
#endif

// WP8 
// TODO How to?

// Check if we got our platform
#if (SANI_TARGET_PLATFORM == SANI_PLATFORM_UNKOWN)
#error "Can not recognize platform"
#endif