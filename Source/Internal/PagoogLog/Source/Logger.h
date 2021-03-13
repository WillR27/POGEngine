#pragma once

#include <spdlog/spdlog.h>

namespace Pagoog::Log
{
	class Logger
	{
	public:
		Logger();

		~Logger() = default;

		void Init();

		template<typename T>
		void Trace(const T& msg)
		{
			logger->trace(msg);
		}

		template<typename T, typename... Args>
		void Trace(const T& fmt, const Args&... args)
		{
			logger->trace(fmt, args...);
		}

		template<typename T>
		void Info(const T& msg)
		{
			logger->info(msg);
		}

		template<typename T, typename... Args>
		void Info(const T& fmt, const Args&... args)
		{
			logger->info(fmt, args...);
		}

		template<typename T>
		void Warn(const T& msg)
		{
			logger->warn(msg);
		}

		template<typename T, typename... Args>
		void Warn(const T& fmt, const Args&... args)
		{
			logger->warn(fmt, args...);
		}

		template<typename T>
		void Error(const T& msg)
		{
			logger->error(msg);
		}

		template<typename T, typename... Args>
		void Error(const T& fmt, const Args&... args)
		{
			logger->error(fmt, args...);
		}

		template<typename T>
		void Critical(const T& msg)
		{
			logger->critical(msg);
		}

		template<typename T, typename... Args>
		void Critical(const T& fmt, const Args&... args)
		{
			logger->critical(fmt, args...);
		}

	private:
		std::shared_ptr<spdlog::logger> logger;
	};
}