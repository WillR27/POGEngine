#include "pgepch.h"
#include "Time.h"

namespace PEngine
{
	float Time::UPS = 100.0f;
	float Time::TimeUntilUpdate = 1.0f / Time::UPS;
	float Time::FPS = 1000.0f;
	float Time::TimeUntilFrame = 1.0f / Time::FPS;

	std::chrono::high_resolution_clock Time::timer;
	std::chrono::time_point<std::chrono::steady_clock> Time::prev;

	void Time::Reset()
	{
		prev = timer.now();
	}

	float Time::DeltaTime()
	{
		auto now = timer.now();
		
		float deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::nano>>(now - prev).count() / 100000000.0f;

		prev = now;

		return deltaTime;
	}
}