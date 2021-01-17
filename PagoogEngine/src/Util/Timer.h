#pragma once

#include <chrono>

namespace PEngine
{
	enum class Unit
	{
		Seconds,
		Milliseconds,
		Microseconds,
		Nanoseconds
	};

	// Units, Type, Decimals
	template <Unit U = Unit::Milliseconds, typename T = float, bool D = false>
	class Timer
	{
	public:
		void Start()
		{
			start = timer.now();
		}

		T End()
		{
			auto end = timer.now();
			
			T divisor = 1000000;
			switch (U)
			{
			case Unit::Seconds:			divisor = 1000000000; break;
			case Unit::Microseconds:	divisor = 1000; break;
			case Unit::Nanoseconds:		divisor = 1; break;
			}

			elapsedTime = std::chrono::duration_cast<std::chrono::duration<T, std::nano>>(end - start).count() / divisor;

			if (!D)
			{
				elapsedTime = static_cast<T>(static_cast<int>(elapsedTime));
			}

			return elapsedTime;
		}

		T Elapsed()
		{
			return elapsedTime;
		}

		std::string ElapsedString()
		{
			const char* unit = "ms";
			switch (U)
			{
			case Unit::Seconds:			unit = "s"; break;
			case Unit::Microseconds:	unit = "us"; break;
			case Unit::Nanoseconds:		unit = "ns"; break;
			}

			std::stringstream ss;
			ss << elapsedTime << unit;
			return ss.str();
		}

	private:
		std::chrono::high_resolution_clock timer = std::chrono::high_resolution_clock();

		std::chrono::time_point<std::chrono::steady_clock> start;

		T elapsedTime = 0.0f;
	};
}

