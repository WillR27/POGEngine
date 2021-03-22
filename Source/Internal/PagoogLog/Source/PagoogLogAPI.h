#pragma once

#ifdef PG_LOG_EXPORT
	#define PG_LOG_API __declspec(dllexport)
#else
	#define PG_LOG_API __declspec(dllimport)
#endif