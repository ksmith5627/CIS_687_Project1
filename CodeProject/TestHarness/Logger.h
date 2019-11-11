#pragma once

#ifndef LOGGER_H
#define LOGGER_H
#endif // !LOGGER_H

#include <iostream>
#include <map>

// Provide aliases for commonly used types that make the code look long
using string = std::string;
using variables = std::map<string, string>;

// Different support log levels
enum LogLevel { BASIC, DETAILED, VERBOSE };

// Defines the basic logger class
class BasicLogger
{
public:
	BasicLogger(int, string, string, bool);
	virtual void LogMessage();
protected:
	bool _result;		// Protected to allow child classes to access its value.
private:
	int _testSequence;	// The index of the test in a test suite.
	string _testName;	// The name of the test/test suite.
	string _testType;	// The type of callable object.
};

// The DetailedLogger, which additionally prints exception info in case of failures
// overrides the base class LogMessage() to add its own implementation
// It derives from BasicLogger
class DetailedLogger : public BasicLogger
{
public:
	DetailedLogger(int, string, string, bool = false, string* = nullptr, std::exception* = nullptr);
	virtual void LogMessage();
	virtual ~DetailedLogger();
private:
	string *_message;				// message to be printed along with the test result
	std::exception * _exception;	// exception whose details have to be printed in case of test failure caused by an unhandled exception
};

// The VerboseLogger, which additionally prints a list of variables
// overrides the base class LogMessage() to add its own implementation
// It also optionally prints the timestamp denoting the time the test was run/
// It derives from DetailedLogger
class VerboseLogger : public DetailedLogger
{
public:
	VerboseLogger(int, string, string, bool = false, string* = nullptr, std::exception* = nullptr, variables* = nullptr, bool = false);
	virtual void LogMessage();
	virtual ~VerboseLogger();
private:
	bool _includeDateTime;		// Flag denoting whether or not the timestamp must be printed
	variables* _variableMap;	// A map of variable names and their values to be printed
};