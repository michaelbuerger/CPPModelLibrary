#include "CPPML/logging/Log.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace CPPML { namespace logging
{
	std::shared_ptr<spdlog::logger> Log::m_logger;

	void Log::Init() // Make sure to run this in CPPModelLoader init method
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		m_logger = spdlog::stdout_color_mt("CPPML");
		m_logger->set_level(spdlog::level::trace);
	}

}}
