#pragma once

#ifdef POG_RENDER_EXPORT
	#define POG_RENDER_API __declspec(dllexport)
#else
	#define POG_RENDER_API __declspec(dllimport)
#endif