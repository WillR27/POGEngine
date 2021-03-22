#pragma once

#ifdef PG_DEBUG_EXPORT
	#define PG_DEBUG_API __declspec(dllexport)
#else
	#define PG_DEBUG_API __declspec(dllimport)
#endif