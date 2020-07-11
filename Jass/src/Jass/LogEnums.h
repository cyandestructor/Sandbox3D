#ifndef LOG_ENUMS_H
#define LOG_ENUMS_H

namespace Jass {

	enum class LoggerType
	{
		CLIENT, CORE
	};

	enum class LogLevel
	{
		TRACE, DEBUG, INFO, WARN, ERR, CRITICAL
	};

}

#endif // !LOG_ENUMS_H
