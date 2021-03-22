#pragma once

#ifdef PG_COMMON_EXPORT
	#define PG_COMMON_API __declspec(dllexport)
#else
	#define PG_COMMON_API __declspec(dllimport)
#endif