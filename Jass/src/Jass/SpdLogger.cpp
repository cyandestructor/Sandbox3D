#include "jasspch.h"
#include "SpdLogger.h"

namespace Jass {

	void SpdLogger::Init(const std::string& loggerName)
	{
		//Check if there is any logger with that name
		m_logger = spdlog::get(loggerName);

		if (!m_logger) {
			m_logger = spdlog::stdout_color_mt(loggerName);
			m_logger->set_pattern("%^[%T] %n: %v%$");
			m_logger->set_level(spdlog::level::trace);
		}
	}

}
