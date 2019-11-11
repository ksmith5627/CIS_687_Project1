#pragma once

#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H
#endif

#include <map>
#include <typeinfo>
#include "Logger.h"
#include "LoggerFactory.h"
// Class - TestHarness
class TestHarness
{
public:
	TestHarness(LogLevel = BASIC, bool = false);

	// Execute a single test, just logging the testname and the result
	template <typename T>
	void ExecuteTest(string testName, T &t)
	{
		ExecuteTest(testName, nullptr, nullptr, t);
	}

	// Execute a single test, additionally logging a message
	template <typename T>
	void ExecuteTest(string testName, string* message, T &t)
	{
		ExecuteTest(testName, message, nullptr, t);
	}
	
	// Execute a single logging a message and a list of variable names and their values.
	template <typename T>
	void ExecuteTest(string testName, string* message, variables* variableMap,  T &t)
	{
		// The declaration for logger could've been prior to the try block, and the call to LogMessage() after the catch block
		// But since in the catch block, we are passing a pointed to the exception, we can't call LogMessage() outside the catch block
		// as the exception will be out of scope.
		try
		{
			// Execute the test
			auto returnValue = t();
			// Initialize logger with results of test
			BasicLogger* logger = _loggerFactory.GetLoggerInstance(++_testSequence, testName, typeid(t).name(), _logLevel, (bool)returnValue, message, nullptr, variableMap, _includeDateTime);
			// Log message.
			logger->LogMessage();
		}
		// Oops, something went wrong.
		catch (std::exception &e)
		{
			// Initialize logger with exception and result set to false
			BasicLogger* logger = _loggerFactory.GetLoggerInstance(++_testSequence, testName, typeid(t).name(), _logLevel, false, message, &e, variableMap, _includeDateTime);
			// Log message.
			logger->LogMessage();
		}
	}

	// Execute a sequence of tests one after the other, in the order passed
	// Just logging the test name and the result
	template <typename Test, typename... Tests>
	void ExecuteTest(string testName, Test& t, Tests&... ts)
	{
		ExecuteTest(testName, t);
		ExecuteTest(testName, ts...);
	}

	// Execute a sequence of tests one after the other, in the order passed
	// Logging the test name, the result, and additionally a message
	template <typename Test, typename... Tests>
	void ExecuteTest(string testName, string* message, Test& t, Tests&... ts)
	{
		ExecuteTest(testName, message, t);
		ExecuteTest(testName, message, ts...);
	}

	// Execute a sequence of tests one after the other, in the order passed
	// Logging the test name, the result, a message and additionally a list of variable names and their values
	template <typename Test, typename... Tests>
	void ExecuteTest(string testName, string* message, variables* variableMap, Test& t, Tests&... ts)
	{
		ExecuteTest(testName, message, variableMap, t);
		ExecuteTest(testName, message, variableMap, ts...);
	}

	// Rest the test sequence back to zero.
	void ResetTestSequence();

	// Change the log level to a new value
	void UpdateLogLevel(LogLevel, bool = false);

private:
	LogLevel _logLevel;
	bool _includeDateTime;
	static LoggerFactory _loggerFactory;
	int _testSequence;
};