#pragma once

#include <spdlog/spdlog.h>

#include "POGLogAPI.h"

namespace POG::Log
{
	class SharedLogger
	{
	public:
		SharedLogger(std::shared_ptr<spdlog::logger> logger);

		spdlog::logger& GetLoggerRef();

	private:
		std::shared_ptr<spdlog::logger> logger;
	};

	class Logger
	{
	public:
		Logger();

		~Logger() = default;

		void Init();


		void Trace(const char* msg)
		{
			logger.GetLoggerRef().trace(msg);
		}

		void Trace(std::string msg)
		{
			logger.GetLoggerRef().trace(msg);
		}

		//template<typename T>
		//void Trace(const T& obj)
		//{
		//	logger.GetLoggerRef().trace(obj.ToString());
		//}

		template<typename T, typename... Args>
		void Trace(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().trace(fmt, args...);
		}


		void Info(const char* msg)
		{
			logger.GetLoggerRef().info(msg);
		}

		void Info(std::string msg)
		{
			logger.GetLoggerRef().info(msg);
		}

		//template<typename T>
		//void Info(const T& obj)
		//{
		//	logger.GetLoggerRef().info(obj.ToString());
		//}

		template<typename T, typename... Args>
		void Info(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().info(fmt, args...);
		}


		void Warn(const char* msg)
		{
			logger.GetLoggerRef().warn(msg);
		}

		void Warn(std::string msg)
		{
			logger.GetLoggerRef().warn(msg);
		}

		//template<typename T>
		//void Warn(const T& obj)
		//{
		//	logger.GetLoggerRef().warn(obj.ToString());
		//}

		template<typename T, typename... Args>
		void Warn(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().warn(fmt, args...);
		}


		void Error(const char* msg)
		{
			logger.GetLoggerRef().error(msg);
		}

		void Error(std::string msg)
		{
			logger.GetLoggerRef().error(msg);
		}

		//template<typename T>
		//void Error(const T& obj)
		//{
		//	logger.GetLoggerRef().error(obj.ToString());
		//}

		template<typename T, typename... Args>
		void Error(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().error(fmt, args...);
		}


		void Critical(const char* msg)
		{
			logger.GetLoggerRef().critical(msg);
		}

		void Critical(std::string msg)
		{
			logger.GetLoggerRef().critical(msg);
		}

		//template<typename T>
		//void Critical(const T& obj)
		//{
		//	logger.GetLoggerRef().critical(obj.ToString());
		//}

		template<typename T, typename... Args>
		void Critical(const T& fmt, const Args&... args)
		{
			logger.GetLoggerRef().critical(fmt, args...);
		}

	private:
		SharedLogger logger;
	};
}