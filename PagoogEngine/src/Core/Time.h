#pragma once

namespace PEngine
{
	class Time
	{
	public:
		static float UPS;
		static float TimeUntilUpdate;
		static float FPS;
		static float TimeUntilFrame;

		static double DeltaTimeUpdate;
		static double DeltaTimeFrame;

		static void Reset();
		static double DeltaTime();

	private: 
		static std::chrono::high_resolution_clock timer;
		static std::chrono::time_point<std::chrono::steady_clock> prev;
	};
}

