#ifndef JASS_LOG_H
#define JASS_LOG_H

#include <memory>
#include "LogEnums.h"

namespace Jass {

	template <typename Logger>
	class Log {

	public:
		Log(const std::shared_ptr<Logger>& coreLogger, const std::shared_ptr<Logger>& clientLogger);

		template <typename FormatString, typename... Args>
		void LogMsg(LoggerType logger, LogLevel logLvl, const FormatString& fmt, const Args& ...args);

	private:
		std::shared_ptr<Logger> m_coreLogger;
		std::shared_ptr<Logger> m_clientLogger;

	};

	template<typename Logger>
	inline Log<Logger>::Log(const std::shared_ptr<Logger>& coreLogger, const std::shared_ptr<Logger>& clientLogger)
		: m_coreLogger(coreLogger), m_clientLogger(clientLogger)
	{
		m_coreLogger->Init("JASS");
		m_clientLogger->Init("APP");
	}

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

}

#endif // !JASS_LOG_H
