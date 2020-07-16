#ifndef JASS_LOG_H
#define JASS_LOG_H

#include "LogEnums.h"

namespace Jass {

	template <typename Logger>
	class Log {

	public:

		template <typename FormatString, typename... Args>
		static void LogMsg(LoggerType logger, LogLevel logLvl, const FormatString& fmt, const Args& ...args);

	private:
		Log() {}
		
		static std::unique_ptr<Logger> m_coreLogger;
		static std::unique_ptr<Logger> m_clientLogger;

	};

	template<typename Logger>
	std::unique_ptr<Logger> Log<Logger>::m_coreLogger = std::make_unique<Logger>("JASS");

	template<typename Logger>
	std::unique_ptr<Logger> Log<Logger>::m_clientLogger = std::make_unique<Logger>("APP");

	template<typename Logger>
	template<typename FormatString, typename ...Args>
	inline void Log<Logger>::LogMsg(LoggerType logger, LogLevel logLvl, const FormatString& fmt, const Args& ...args)
	{
		switch (logger) {
		case LoggerType::CLIENT:
			m_clientLogger->Log(logLvl, fmt, args...);
			break;
		case LoggerType::CORE:
			m_coreLogger->Log(logLvl, fmt, args...);
			break;
		}
	}

#define JASS_CORE_TRACE(type, ...)		Jass::Log<type>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::TRACE, __VA_ARGS__)
#define JASS_CORE_INFO(type, ...)		Jass::Log<type>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::INFO, __VA_ARGS__)
#define JASS_CORE_DEBUG(type, ...)		Jass::Log<type>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::DEBUG, __VA_ARGS__)
#define JASS_CORE_WARN(type, ...)		Jass::Log<type>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::WARN, __VA_ARGS__)
#define JASS_CORE_ERR(type, ...)		Jass::Log<type>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::ERR, __VA_ARGS__)
#define JASS_CORE_CRITICAL(type, ...)	Jass::Log<type>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::CRITICAL, __VA_ARGS__)

#define JASS_CLIENT_TRACE(type, ...)	Jass::Log<type>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::TRACE, __VA_ARGS__)
#define JASS_CLIENT_INFO(type, ...)		Jass::Log<type>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::INFO, __VA_ARGS__)
#define JASS_CLIENT_DEBUG(type, ...)	Jass::Log<type>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::DEBUG, __VA_ARGS__)
#define JASS_CLIENT_WARN(type, ...)		Jass::Log<type>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::WARN, __VA_ARGS__)
#define JASS_CLIENT_ERR(type, ...)		Jass::Log<type>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::ERR, __VA_ARGS__)
#define JASS_CLIENT_CRITICAL(type, ...)	Jass::Log<type>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::CRITICAL, __VA_ARGS__)

}

#endif // !JASS_LOG_H
