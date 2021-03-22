#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

#include "PagoogLogAPI.h"

#include "Logger.h"

namespace Pagoog::Log
{
	class Log
	{
	public:
		static PG_LOG_API void Init();

		static PG_LOG_API Logger& GetLogger() { return GetLoggerRef(); }

	private:
		static std::shared_ptr<Logger> Logger;

		static PG_LOG_API Pagoog::Log::Logger& GetLoggerRef();
	};
}

#ifdef PG_DEBUG

#define PG_TRACE(...)					::Pagoog::Log::Log::GetLogger().Trace("{0} {1}({2})", PG_FUNC, PG_FILENAME, PG_LINE);		::Pagoog::Log::Log::GetLogger().Trace(__VA_ARGS__);
#define PG_INFO(...)					::Pagoog::Log::Log::GetLogger().Info("{0} {1}({2})", PG_FUNC, PG_FILENAME, PG_LINE);		::Pagoog::Log::Log::GetLogger().Info(__VA_ARGS__);
#define PG_WARN(...)					::Pagoog::Log::Log::GetLogger().Warn("{0} {1}({2})", PG_FUNC, PG_FILENAME, PG_LINE);		::Pagoog::Log::Log::GetLogger().Warn(__VA_ARGS__);
#define PG_ERROR(...)					::Pagoog::Log::Log::GetLogger().Error("{0} {1}({2})", PG_FUNC, PG_FILENAME, PG_LINE);		::Pagoog::Log::Log::GetLogger().Error(__VA_ARGS__);
#define PG_CRITICAL(...)				::Pagoog::Log::Log::GetLogger().Critical("{0} {1}({2})", PG_FUNC, PG_FILENAME, PG_LINE);	::Pagoog::Log::Log::GetLogger().Critical(__VA_ARGS__);

#endif
#ifdef PG_RELEASE

#define PG_TRACE(...)					
#define PG_INFO(...)					::Pagoog::Log::Log::GetLogger().Info(__VA_ARGS__);
#define PG_WARN(...)					::Pagoog::Log::Log::GetLogger().Warn(__VA_ARGS__);
#define PG_ERROR(...)					::Pagoog::Log::Log::GetLogger().Error(__VA_ARGS__);
#define PG_CRITICAL(...)				::Pagoog::Log::Log::GetLogger().Critical(__VA_ARGS__);

#endif
#ifdef PG_DIST

#define PG_TRACE(...)					
#define PG_INFO(...)					
#define PG_WARN(...)					::Pagoog::Log::Log::GetLogger().Warn(__VA_ARGS__);
#define PG_ERROR(...)					::Pagoog::Log::Log::GetLogger().Error(__VA_ARGS__);
#define PG_CRITICAL(...)				::Pagoog::Log::Log::GetLogger().Critical(__VA_ARGS__);

#endif

