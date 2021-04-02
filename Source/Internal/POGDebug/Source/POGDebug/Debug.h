#pragma once

#ifdef POG_ENABLE_ASSERT
	#define POG_VERIFY(x, ...) { if (!(x)) { POG_WARN("Verification Failed: {0}", #x); POG_WARN(__VA_ARGS__); } }
	#define POG_ASSERT(x, ...) { if (!(x)) { POG_ERROR("Assertion Failed: {0}", #x); POG_ERROR(__VA_ARGS__); __debugbreak(); } }
#elif POG_ENABLE_VERIFY
	#define POG_VERIFY(x, ...) { if (!(x)) { POG_WARN("Verification Failed: {0}", #x); POG_WARN(__VA_ARGS__); } }
	#define POG_ASSERT(x, ...) POG_VERIFY(x, __VA_ARGS__)
#else
	#define POG_VERIFY(x, ...)
	#define POG_ASSERT(x, ...)
#endif

#include "POGDebugAPI.h"

// TODO: Just here to get the dll/lib to build
POG_DEBUG_API void Placeholder();