#pragma once

#include "Debug/Log/Log.h"
#include "Util/Timer.h"

namespace PEngine
{
	template <Unit U = Unit::Microseconds, typename T = float>
	class ScopedProfile
	{
	public:
		ScopedProfile(const char* function = "", int line = -1, const char* msg = "Time taken")
			: function(function)
			, line(line)
			, msg(msg)
		{
			timer.Start();
		}

		~ScopedProfile()
		{
			timer.End();

			if (line > 0)
			{
				PG_TRACE_NO_LINE("[{0}:{1}] {2}: {3}", function, line, msg, timer.ElapsedString());
			}
			else
			{
				PG_TRACE("{0}: {1}", msg, timer.ElapsedString());
			}
		}

	private:
		Timer<U> timer;

		const char* function;
		int line;
		const char* msg;
	};
}

#define PG_SCOPED_PROFILE(msg) ScopedProfile<Unit::Microseconds> scopedProfile(__FUNCTION__, __LINE__, msg)
//#define PG_SCOPED_PROFILE_NO_MSG() ScopedProfile<> scopedProfile(__FUNCTION__, __LINE__)

#define PG_START_SCOPED_PROFILE(msg) { ScopedProfile<Unit::Microseconds> scopedProfile(__FUNCTION__, __LINE__, msg)
//#define PG_START_SCOPED_PROFILE_NO_MSG() { ScopedProfile<> scopedProfile(__FUNCTION__, __LINE__)
#define PG_END_SCOPED_PROFILE() }

//#define GET_2ND_ARG(arg1, arg2, ...) arg2
//
//#define PG_SCOPED_PROFILE_MACRO_CHOOSER(...) GET_2ND_ARG(__VA_ARGS__, PG_SCOPED_PROFILE_MSG, PG_SCOPED_PROFILE_NO_MSG)
//#define PG_SCOPED_PROFILE(...) PG_SCOPED_PROFILE_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
//
//#define PG_START_SCOPED_PROFILE_MACRO_CHOOSER(...) GET_2ND_ARG(__VA_ARGS__, PG_START_SCOPED_PROFILE_MSG, PG_START_SCOPED_PROFILE_NO_MSG)
//#define PG_START_SCOPED_PROFILE(...) PG_START_SCOPED_PROFILE_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
