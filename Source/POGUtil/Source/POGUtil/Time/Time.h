#pragma once

#include <chrono>

namespace POG::Util
{
	class Time
	{
	public:
		enum class Unit
		{
			Seconds,
			Milliseconds,
			Microseconds,
			Nanoseconds
		};
	};

	// Units, Type, Decimals
	template <Time::Unit U = Time::Unit::Milliseconds, typename T = float, bool D = false>
	class Timer
	{
	public:
		void Start()
		{
			start = timer.now();
			stopped = false;
		}

		T Stop()
		{
			T elapsed = Elapsed();
			stopped = true;

			return elapsed;
		}

		void Reset()
		{
			elapsedTime = 0;
			start = timer.now();
		}

		T Elapsed()
		{
			if (!stopped)
			{
				end = timer.now();

				T divisor = 1000000;
				switch (U)
				{
				case Time::Unit::Seconds:			divisor = 1000000000; break;
				case Time::Unit::Microseconds:		divisor = 1000; break;
				case Time::Unit::Nanoseconds:		divisor = 1; break;
				}

				T deltaTime = std::chrono::duration_cast<std::chrono::duration<T, std::nano>>(end - start).count() / divisor;

				if (!D)
				{
					elapsedTime += static_cast<T>(static_cast<int>(deltaTime));
				}
				else
				{
					elapsedTime += deltaTime;
				}

				start = end;
			}

			return elapsedTime;
		}

		std::string ElapsedString()
		{
			const char* unit = "ms";
			switch (U)
			{
			case Time::Unit::Seconds:			unit = "s"; break;
			case Time::Unit::Microseconds:		unit = "us"; break;
			case Time::Unit::Nanoseconds:		unit = "ns"; break;
			}

			std::stringstream ss;
			ss << elapsedTime << unit;
			return ss.str();
		}

	private:
		std::chrono::high_resolution_clock timer = std::chrono::high_resolution_clock();

		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> end;

		T elapsedTime = 0;
		bool stopped = true;
	};
}

