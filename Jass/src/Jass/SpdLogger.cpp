#include "SpdLogger.h"

void Jass::SpdLogger::Init(const std::string& loggerName)
{
	m_logger = spdlog::stdout_color_mt(loggerName);
	m_logger->set_pattern("%^[%T] %n: %v%$");
	m_logger->set_level(spdlog::level::trace);
}
