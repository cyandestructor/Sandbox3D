#ifndef JASS_SPDLOGGER_H
#define JASS_SPDLOGGER_H

#include <memory>
#include <exception>

#include "Core.h"
#include "LogEnums.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Jass {

	class JASS_API SpdLogger {

	public:
		SpdLogger() : m_logger(nullptr) {}

		void Init(const std::string&);

		template <typename FormatString, typename... Args>
		void Log(LogLevel, const FormatString&, const Args& ...);
	private:
		std::shared_ptr<spdlog::logger> m_logger;

	};

	template<typename FormatString, typename ...Args>
	inline void SpdLogger::Log(LogLevel logLvl, const FormatString& fmt, const Args& ...args)
	{
		if (m_logger == nullptr)
			throw std::runtime_error("Cannot Log before using Init");

		spdlog::level::level_enum level;

		switch (logLvl) {
		case LogLevel::TRACE:
			level = spdlog::level::level_enum::trace;
			break;
		case LogLevel::DEBUG:
			level = spdlog::level::level_enum::debug;
			break;
		case LogLevel::INFO:
			level = spdlog::level::level_enum::info;
			break;
		case LogLevel::WARN:
			level = spdlog::level::level_enum::warn;
			break;
		case LogLevel::ERR:
			level = spdlog::level::level_enum::err;
			break;
		case LogLevel::CRITICAL:
			level = spdlog::level::level_enum::critical;
			break;
		}

		m_logger->log(level, fmt, args...);
	}

}

#endif // !JASS_SPDLOGGER_H
