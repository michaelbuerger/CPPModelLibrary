/* Note: Must define CPPML_DEBUG_OFF before inclusion of this header to turn off logging */
#ifndef LOG_HPP
#define LOG_HPP

#include <memory>
#include "spdlog/spdlog.h"

namespace CPPML { namespace logging
{
	class Log
	{
	    private:
		    static std::shared_ptr<spdlog::logger> m_logger;
	    public:
		    static void Init();

		    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_logger; };
	};

}}

// TODO: Turn this off by default for library release, allow individual levels to be enabled

#ifndef CPPML_DEBUG_LOG_OFF

#define CPPML_TRACE(...) CPPML::logging::Log::GetLogger()->trace(__VA_ARGS__)
#define CPPML_INFO(...) CPPML::logging::Log::GetLogger()->info(__VA_ARGS__)
#define CPPML_WARN(...) CPPML::logging::Log::GetLogger()->warn(__VA_ARGS__)
#define CPPML_ERROR(...) CPPML::logging::Log::GetLogger()->error(__VA_ARGS__)
#define CPPML_CRIT(...) CPPML::logging::Log::GetLogger()->critical(__VA_ARGS__)

#endif

#endif /* end of include guard LOG_HPP */