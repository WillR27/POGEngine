#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#define SPDLOG_DEBUG_ON
#define SPDLOG_TRACE_ON

#include "POGCommon.h"

#include "Logger.h"

namespace POG::Log
{
	class Log
	{
	public:
		static void Init();

		static Logger& GetLogger() { return GetLoggerRef(); }

	private:
		static std::shared_ptr<Logger> Logger;

		static POG::Log::Logger& GetLoggerRef();
	};
}

#ifdef POG_DEBUG

#define POG_TRACE(...)					::POG::Log::Log::GetLogger().Trace("{0} {1}({2})", POG_FUNCTION_SIGNATURE, POG_FILENAME, POG_LINE_NUMBER);		::POG::Log::Log::GetLogger().Trace(__VA_ARGS__);
#define POG_INFO(...)					::POG::Log::Log::GetLogger().Info("{0} {1}({2})", POG_FUNCTION_SIGNATURE, POG_FILENAME, POG_LINE_NUMBER);		::POG::Log::Log::GetLogger().Info(__VA_ARGS__);
#define POG_WARN(...)					::POG::Log::Log::GetLogger().Warn("{0} {1}({2})", POG_FUNCTION_SIGNATURE, POG_FILENAME, POG_LINE_NUMBER);		::POG::Log::Log::GetLogger().Warn(__VA_ARGS__);
#define POG_ERROR(...)					::POG::Log::Log::GetLogger().Error("{0} {1}({2})", POG_FUNCTION_SIGNATURE, POG_FILENAME, POG_LINE_NUMBER);		::POG::Log::Log::GetLogger().Error(__VA_ARGS__);
#define POG_CRITICAL(...)				::POG::Log::Log::GetLogger().Critical("{0} {1}({2})", POG_FUNCTION_SIGNATURE, POG_FILENAME, POG_LINE_NUMBER);	::POG::Log::Log::GetLogger().Critical(__VA_ARGS__);

#endif
#ifdef POG_RELEASE

#define POG_TRACE(...)					
#define POG_INFO(...)					::POG::Log::Log::GetLogger().Info(__VA_ARGS__);
#define POG_WARN(...)					::POG::Log::Log::GetLogger().Warn(__VA_ARGS__);
#define POG_ERROR(...)					::POG::Log::Log::GetLogger().Error(__VA_ARGS__);
#define POG_CRITICAL(...)				::POG::Log::Log::GetLogger().Critical(__VA_ARGS__);

#endif
#ifdef POG_DIST

#define POG_TRACE(...)					
#define POG_INFO(...)					
#define POG_WARN(...)					::POG::Log::Log::GetLogger().Warn(__VA_ARGS__);
#define POG_ERROR(...)					::POG::Log::Log::GetLogger().Error(__VA_ARGS__);
#define POG_CRITICAL(...)				::POG::Log::Log::GetLogger().Critical(__VA_ARGS__);

#endif

