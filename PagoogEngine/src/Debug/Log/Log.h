#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace PEngine
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetLogger() { return Logger; }

	private:
		static std::shared_ptr<spdlog::logger> Logger;
	};
}

#define PG_TRACE_NO_LINE(...)			::PEngine::Log::GetLogger()->trace(__VA_ARGS__)
#define PG_INFO_NO_LINE(...)			::PEngine::Log::GetLogger()->info(__VA_ARGS__)
#define PG_WARN_NO_LINE(...)			::PEngine::Log::GetLogger()->warn(__VA_ARGS__)
#define PG_ERROR_NO_LINE(...)			::PEngine::Log::GetLogger()->error(__VA_ARGS__)
#define PG_CRITICAL_NO_LINE(...)		::PEngine::Log::GetLogger()->critical(__VA_ARGS__)

#ifdef PG_DEBUG

#define PG_TRACE(...)					SPDLOG_TRACE(__VA_ARGS__)
#define PG_INFO(...)					SPDLOG_INFO(__VA_ARGS__)
#define PG_WARN(...)					SPDLOG_WARN(__VA_ARGS__)
#define PG_ERROR(...)					SPDLOG_ERROR(__VA_ARGS__)
#define PG_CRITICAL(...)				SPDLOG_CRITICAL(__VA_ARGS__)

#else

#define PG_TRACE(...)					PG_TRACE_NO_LINE(__VA_ARGS__)	
#define PG_INFO(...)					PG_INFO_NO_LINE(__VA_ARGS__)	
#define PG_WARN(...)					PG_WARN_NO_LINE(__VA_ARGS__)	
#define PG_ERROR(...)					PG_ERROR_NO_LINE(__VA_ARGS__)	
#define PG_CRITICAL(...)				PG_CRITICAL_NO_LINE(__VA_ARGS__)

#endif