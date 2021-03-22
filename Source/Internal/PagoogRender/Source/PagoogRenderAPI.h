#pragma once

#ifdef PG_RENDER_EXPORT
	#define PG_RENDER_API __declspec(dllexport)
#else
	#define PG_RENDER_API __declspec(dllimport)
#endif