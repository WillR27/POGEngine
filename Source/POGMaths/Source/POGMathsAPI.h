#pragma once

#ifdef POG_MATHS_EXPORT
	#define POG_MATHS_API __declspec(dllexport)
#else
	#define POG_MATHS_API __declspec(dllimport)
#endif

// Placeholder just to force the dll to be built
class POG_MATHS_API Placeholder
{

};