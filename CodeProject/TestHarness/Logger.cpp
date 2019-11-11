#include "stdafx.h"

#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

// Constructor for the BasicLogger. Just copying over values into its private members.
BasicLogger::BasicLogger(int testSequence, string testName, string testType, bool result)
	:_testSequence(testSequence), _testName(testName), _testType(testType), _result(result)
{
}

// The LogMessage() for BasicLogger just prints the
// testname, the index of the test, and the type of callable object
// followed by the test result.
void BasicLogger::LogMessage()
{
	std::cout << _testName << "_" << _testSequence << ": (" << _testType;
	if (_result)
		std::cout << ") passed";
	else
		std::cout << ") failed";
	std::cout << std::endl;
}

// The constructor for the Detailed Logger
// Calls the BasicLogger constructor
// Additionally sets the message and the exception pointer
DetailedLogger::DetailedLogger(int testSequence, string testName, string testType, bool result, string* message, std::exception* exception)
	: BasicLogger::BasicLogger(testSequence, testName, testType, result), _message(message), _exception(exception)
{
}

// The destructor for the DetailedLogger
// Frees up message & exception if they were set.
DetailedLogger::~DetailedLogger()
{
	if (_message != nullptr)
		free(_message);
	if (_exception != nullptr)
		free(_exception);
}

// The LogMessage() for the DetailedLogger
// Prints the base LogMessage() and an optional message
// If the exception is set, it prints it too.
void DetailedLogger::LogMessage()
{
	BasicLogger::LogMessage();
	if(_message != nullptr)
		std::cout << "Test message: " << *_message << std::endl;
	if (_exception != nullptr)
		std::cout << "Exception thrown during test execution: " << _exception->what() << std::endl;
}

// The constructor for the Verbose Logger
// Calls the DetailedLogger constructor
// Additionally sets the _includeDateTime flag & the variable list, if any.
VerboseLogger::VerboseLogger(int testSequence, string testName, string testType, bool result, string* message, std::exception* exception, variables* variableMap, bool includeDateTime)
	: DetailedLogger::DetailedLogger(testSequence, testName, testType, result, message, exception), _includeDateTime(includeDateTime), _variableMap(variableMap)
{
}

// The destructor for the VerboseLogger
// Frees up the variable map, if set.
VerboseLogger::~VerboseLogger()
{
	if (_variableMap != nullptr)
		free(_variableMap);
}

// The LogMessage() for the VerboseLogger
// First prints the current time stamp if _includeDateTime
// flag was set, and then proceeds to print log message
// per its base class.
// It finishes off by printing the variables in the callable object
// and their values (passed through constructor)
void VerboseLogger::LogMessage()
{
	if (_includeDateTime)
	{
		auto now = std::chrono::system_clock::now();
		auto now_c = std::chrono::system_clock::to_time_t(now);
		std::cout << "[" << std::put_time(std::localtime(&now_c), "%c") << "] " ;
	}
	DetailedLogger::LogMessage();
	if (_variableMap != nullptr)
	{
		std::cout << "Variables: " << std::endl;
		for (variables::iterator iterator = _variableMap->begin(); iterator != _variableMap->end(); ++iterator)
		{
			std::cout << iterator->first << " => " << iterator->second << "\n";
		}
	}
}