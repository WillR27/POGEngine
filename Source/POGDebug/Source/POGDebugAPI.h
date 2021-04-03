#pragma once

#ifdef POG_DEBUG_EXPORT
	#define POG_DEBUG_API __declspec(dllexport)
#else
	#define POG_DEBUG_API __declspec(dllimport)
#endif