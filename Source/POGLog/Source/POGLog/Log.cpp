#include "POGLogPCH.h"
#include "Log.h"

#include "Logger.h"

namespace POG::Log
{ 
	std::shared_ptr<Logger> Log::Logger(nullptr);

	void Log::Init()
	{
		Log::Logger = std::make_shared<POG::Log::Logger>();
		Log::Logger->Init();
	}

	Logger& Log::GetLoggerRef()
	{
		return *Logger;
	}
}