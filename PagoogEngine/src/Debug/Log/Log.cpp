#include "pgepch.h"
#include "Log.h"

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

namespace PEngine
{
	std::shared_ptr<spdlog::logger> Log::Logger;

	void Log::Init()
	{
		//spdlog::set_pattern("%^[%T] %v%$");
		spdlog::set_pattern("%^[%T] [%!:%#] %v%$");
		//spdlog::set_pattern("%^[%T] [%s] [%!] [Line %#] %v%$");
		spdlog::stdout_logger_mt("console");
		spdlog::set_level(spdlog::level::trace);

		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
		//logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Log.log", true));

		logSinks[0]->set_pattern("%^[%T] %n %v%$");
		//logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		Logger = std::make_shared<spdlog::logger>("Pagoog", begin(logSinks), end(logSinks));
		spdlog::register_logger(Logger);
		Logger->set_level(spdlog::level::trace);
		Logger->flush_on(spdlog::level::trace);
	}
}