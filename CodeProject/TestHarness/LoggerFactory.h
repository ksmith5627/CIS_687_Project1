#pragma once

#ifndef LOG_FACTORY_H
#define LOG_FACTORY_H
#endif // !LOG_FACTORY_H

#include "Logger.h"

class LoggerFactory
{
public:
	// Have a static function return a Logger instance.
	static BasicLogger* GetLoggerInstance(int, string, string, LogLevel, bool = false, string* = nullptr, std::exception* = nullptr, variables* = nullptr, bool = false);
};
