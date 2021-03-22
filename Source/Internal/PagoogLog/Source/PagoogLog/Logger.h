#pragma once

#include <spdlog/spdlog.h>

#include "PagoogLogAPI.h"

namespace Pagoog::Log
{
	class SharedLogger
	{
	public:
		SharedLogger(std::shared_ptr<spdlog::logger> logger);

		PG_LOG_API spdlog::logger& GetLoggerRef();

	private:
		std::shared_ptr<spdlog::logger> logger;
	};

	class Logger
	{
	public:
		Logger();

		~Logger() = default;

		void Init();

		template<typename T>
		void Trace(const T& msg)
		{
			logger.GetLoggerRef().trace(msg);
		}

		template<typename T, typename... Args>
		void Trace(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().trace(fmt, args...);
		}

		template<typename T>
		void Info(const T& msg)
		{
			logger.GetLoggerRef().info(msg);
		}

		template<typename T, typename... Args>
		void Info(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().info(fmt, args...);
		}

		template<typename T>
		void Warn(const T& msg)
		{
			logger.GetLoggerRef().warn(msg);
		}

		template<typename T, typename... Args>
		void Warn(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().warn(fmt, args...);
		}

		template<typename T>
		void Error(const T& msg)
		{
			logger.GetLoggerRef().error(msg);
		}

		template<typename T, typename... Args>
		void Error(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().error(fmt, args...);
		}

		template<typename T>
		void Critical(const T& msg)
		{
			logger.GetLoggerRef().critical(msg);
		}

		template<typename T, typename... Args>
		void Critical(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().critical(fmt, args...);
		}

	private:
		SharedLogger logger;
	};
}