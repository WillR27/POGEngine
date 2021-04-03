#pragma once

#ifdef POG_CORE_EXPORT
	#define POG_CORE_API __declspec(dllexport)
#else
	#define POG_CORE_API __declspec(dllimport)
#endif