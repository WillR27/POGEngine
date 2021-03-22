#pragma once

#ifdef PG_CORE_EXPORT
	#define PG_CORE_API __declspec(dllexport)
#else
	#define PG_CORE_API __declspec(dllimport)
#endif