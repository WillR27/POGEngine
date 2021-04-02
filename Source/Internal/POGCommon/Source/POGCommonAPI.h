#pragma once

#ifdef POG_COMMON_EXPORT
	#define POG_COMMON_API __declspec(dllexport)
#else
	#define POG_COMMON_API __declspec(dllimport)
#endif