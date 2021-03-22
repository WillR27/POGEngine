#include "PagoogLogPCH.h"
#include "Logger.h"

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

namespace Pagoog::Log
{
	Logger::Logger()
		: logger(nullptr)
	{
	}

	void Logger::Init()
	{
		//spdlog::set_pattern("%^[%T] %v%$");
		spdlog::set_pattern("%^[%T] [%!:%#] %v%$");
		//spdlog::set_pattern("%^[%T] [%s] [%!] [Line %#] %v%$");
		spdlog::stdout_logger_mt("console");
		spdlog::set_level(spdlog::level::trace);

		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
		//logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Log.log", true));

		logSinks[0]->set_pattern("%^[%Y/%m/%d %T] %v%$");
		//logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		std::shared_ptr logger = std::make_shared<spdlog::logger>("Pagoog", begin(logSinks), end(logSinks));
		spdlog::register_logger(logger);
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		this->logger = SharedLogger(logger);
	}

	SharedLogger::SharedLogger(std::shared_ptr<spdlog::logger> logger)
		: logger(logger)
	{
	}

	spdlog::logger& SharedLogger::GetLoggerRef()
	{
		return *logger;
	}
}