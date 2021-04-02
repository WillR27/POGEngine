#pragma once

#ifdef POG_LOG_EXPORT
	#define POG_LOG_API __declspec(dllexport)
#else
	#define POG_LOG_API __declspec(dllimport)
#endif