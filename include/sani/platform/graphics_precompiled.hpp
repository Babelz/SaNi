#pragma once

/* Includes */
#include "sani/platform/viewport.hpp"
#include "sani/precompiled.hpp"
#include <functional>

/* Type definitions */
typedef	int32 Buffer;
typedef int32 Shader;

/* Enumerations */
enum GraphicsErrorType {
	NoError,
	BufferError,
	ShaderError,
	InitializationError,
	OutOfMemory
};

/* Struct */