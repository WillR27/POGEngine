#include "pgepch.h"
#include "Time.h"

namespace PEngine
{
	float Time::UPS = 1.0f;
	float Time::TimeUntilUpdate = 1.0f / Time::UPS;
	float Time::FPS = 1000.0f;
	float Time::TimeUntilFrame = 1.0f / Time::FPS;

	double Time::DeltaTimeUpdate = 0.0;
	double Time::DeltaTimeFrame = 0.0;

	std::chrono::high_resolution_clock Time::timer;
	std::chrono::time_point<std::chrono::steady_clock> Time::prev;

	void Time::Reset()
	{
		prev = timer.now();
	}

	double Time::DeltaTime()
	{
		std::chrono::time_point<std::chrono::steady_clock> now = timer.now();
		
		double deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::nano>>(now - prev).count() / 100000000.0;

		prev = now;

		return deltaTime;
	}
}