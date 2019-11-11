#include "stdafx.h"

// Return an instance of the correct logger based on the LogLevel
//
// NOTE: There is no need for a LogLevel enum
//
// The log level is deducible from the arguments passed.
// If variable map is passed, return VerboseLogger instance.
// If message is passed, return DetailedLogger instance.
// return BasicLogger instance.
//
// But this was done to leave the choice of logger to the caller.
// If someone wants to pass a message, and a variable map, yet only choose to do a basic log, its their choice.

BasicLogger* LoggerFactory::GetLoggerInstance(int testSequence, std::string testName, std::string testType, LogLevel logLevel, bool result, string *message, std::exception* exception, std::map<std::string, std::string>* variableMap, bool includeDateTime)
{
	// Based on the log level, instantiate the right logger and return.
	switch (logLevel)
	{
	case VERBOSE:
		return new VerboseLogger(testSequence, testName, testType, result, message, exception, variableMap, includeDateTime);
		break;
	case DETAILED:
		return new DetailedLogger(testSequence, testName, testType, result, message, exception);
		break;
	case BASIC:
	default:
		return new BasicLogger(testSequence, testName, testType, result);
		break;
	}
}