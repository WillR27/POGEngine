#pragma once

#ifdef PG_MATHS_EXPORT
	#define PG_MATHS_API __declspec(dllexport)
#else
	#define PG_MATHS_API __declspec(dllimport)
#endif

// Placeholder just to force the dll to be built
class PG_MATHS_API Placeholder
{

};