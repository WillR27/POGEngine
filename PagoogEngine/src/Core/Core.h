#pragma once

#ifdef PG_ENABLE_ASSERT
	#define PG_VERIFY(x, ...) { if (!x) { PG_WARN("Verification Failed: {0}", __VA_ARGS__); } }
	#define PG_ASSERT(x, ...) { if (!x) { PG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#elif PG_ENABLE_VERIFY
	#define PG_VERIFY(x, ...) { if (!x) { PG_WARN("Verification Failed: {0}", __VA_ARGS__); } }
	#define PG_ASSERT(x, ...) PG_VERIFY(x, __VA_ARGS__)
#else
	#define PG_VERIFY(x, ...)
	#define PG_ASSERT(x, ...)
#endif

#define PG_BIND_FN(fn)        [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define PG_STATIC_BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return fn(std::forward<decltype(args)>(args)...); }