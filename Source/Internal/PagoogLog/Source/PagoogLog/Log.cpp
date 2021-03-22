#include "PagoogLogPCH.h"
#include "Log.h"

#include "Logger.h"

namespace Pagoog::Log
{ 
	std::shared_ptr<Logger> Log::Logger(nullptr);

	void Log::Init()
	{
		Log::Logger = std::make_shared<Pagoog::Log::Logger>();
		Log::Logger->Init();
	}

	Logger& Log::GetLoggerRef()
	{
		return *Logger;
	}
}