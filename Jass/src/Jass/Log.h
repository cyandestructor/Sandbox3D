#ifndef JASS_LOG_H
#define JASS_LOG_H

#include "SpdLogger.h"
#include "LogEnums.h"

namespace Jass {

	typedef SpdLogger MainLogger;

	template <typename Logger = MainLogger>
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

#define JASS_CORE_TRACE(...)		Jass::Log<>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::TRACE, __VA_ARGS__)
#define JASS_CORE_INFO(...)			Jass::Log<>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::INFO, __VA_ARGS__)
#define JASS_CORE_DEBUG(...)		Jass::Log<>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::DEBUG, __VA_ARGS__)
#define JASS_CORE_WARN(...)			Jass::Log<>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::WARN, __VA_ARGS__)
#define JASS_CORE_ERR(...)			Jass::Log<>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::ERR, __VA_ARGS__)
#define JASS_CORE_CRITICAL(...)		Jass::Log<>::LogMsg(Jass::LoggerType::CORE, Jass::LogLevel::CRITICAL, __VA_ARGS__)

#define JASS_CLIENT_TRACE(...)		Jass::Log<>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::TRACE, __VA_ARGS__)
#define JASS_CLIENT_INFO(...)		Jass::Log<>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::INFO, __VA_ARGS__)
#define JASS_CLIENT_DEBUG(...)		Jass::Log<>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::DEBUG, __VA_ARGS__)
#define JASS_CLIENT_WARN(...)		Jass::Log<>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::WARN, __VA_ARGS__)
#define JASS_CLIENT_ERR(...)		Jass::Log<>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::ERR, __VA_ARGS__)
#define JASS_CLIENT_CRITICAL(...)	Jass::Log<>::LogMsg(Jass::LoggerType::CLIENT, Jass::LogLevel::CRITICAL, __VA_ARGS__)

}

#endif // !JASS_LOG_H
