#pragma once

#include "Log/Log.h"

#ifdef PG_ENABLE_ASSERT
	#define PG_VERIFY(x, ...) { if (!(x)) { PG_WARN("Verification Failed: {0}", #x); PG_WARN(__VA_ARGS__); } }
	#define PG_ASSERT(x, ...) { if (!(x)) { PG_ERROR("Assertion Failed: {0}", #x); PG_ERROR(__VA_ARGS__); __debugbreak(); } }
#elif PG_ENABLE_VERIFY
	#define PG_VERIFY(x, ...) { if (!(x)) { PG_WARN("Verification Failed: {0}", #x); PG_WARN(__VA_ARGS__); } }
	#define PG_ASSERT(x, ...) PG_VERIFY(x, __VA_ARGS__)
#else
	#define PG_VERIFY(x, ...)
	#define PG_ASSERT(x, ...)
#endif