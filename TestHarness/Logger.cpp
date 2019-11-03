
/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 1
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University

Program Focus:      The purpose of this program is to test functions using a created test harness.
					The user can run the program within the Visual Studio IDE and the test output will be written
					to the generated console window.

File Description:	This file is the implementation of implementation class that will determine the log level
					that will be used based on the passed arguments.

Implementation File
Details:			The factory will 'return' an instance of the proper and expected logger based LogLevel

					1. The log level is determined from the passed arguments.
					2. Note: If a variable map is passed then a VerboseLogger instance is returned.
					3. Note: If message is passed the a DetailedLogger instance is returned.
					4, By default the BasicLogger instance is returned.

Function  Info:     A member function definition for a class are stored in a separate .cpp file,
					which is called the class implementation file. The file usually has the same
					name as the class, with the .cpp extension. For example the Time class member
					functions would be defined in the file Time.cpp. The file name could be simularly
					named.
*/
/*********************************************************************************************************/

#include "stdafx.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::endl;
using std::put_time;
using std::localtime;
using std::chrono::system_clock;

/*************************************************************************/
// Constructor for the BasicLogger. 
// Values are copied and assigned to their private members.
BasicLogger::BasicLogger(int testSequence, string testName, string testType, bool result)
	:_testSequence(testSequence), _testName(testName), _testType(testType), _result(result)
{
	// Constructor for the Basic_logger function.
	// Copies values into its private members.
}

// Function LogMessage()
// Prints the following:
// 1. Testname
// 2. The index of the test
// 3. The callable object type
// 4. The test result.
void BasicLogger::LogMessage()
{
	cout << _testName << "_" << _testSequence << ": (" << _testType;
	if (_result)
	{
		cout << ") has passed";
	}
	else
	{
		cout << ") has failed";
	}
	cout << std::endl;
}
/*************************************************************************/

// The DetailedLogger() constructor:
// 1. Calls the BasicLogger constructor
// 2. Additionally sets the message and the exception pointer
DetailedLogger::DetailedLogger(int testSequence, string testName, string testType, bool result, string* message, std::exception* exception)
	: BasicLogger::BasicLogger(testSequence, testName, testType, result), _message(message), _exception(exception)
{
	// Constructor for the DetailedLogger
}

// The DetailedLogger destructor
// If set this destructor frees up the message & exception.
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
		cout << "Test message: " << *_message << std::endl;
	if (_exception != nullptr)
		cout << "Exception thrown during test execution: " << _exception->what() << std::endl;
}

// The Verbose Logger constructor
VerboseLogger::VerboseLogger(int testSequence, string testName, string testType, bool result, string* message, std::exception* exception, variables* variableMap, bool includeDateTime)
	: DetailedLogger::DetailedLogger(testSequence, testName, testType, result, message, exception), _includeDateTime(includeDateTime), _variableMap(variableMap)
{
	// 1. VerboseLogger calls the DetailedLogger constructor.
	// 2. Sets the _includeDateTime flag & the variable list.
}

// VerboseLogger destructor:
// If set frees up the variable map.
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
		auto now = system_clock::now();
		auto now_c = system_clock::to_time_t(now);
		
		cout << "[" << put_time(localtime(&now_c), "%c") << "] ";
	}
	DetailedLogger::LogMessage();
	if (_variableMap != nullptr)
	{
		cout << "Variables: " << endl;
		for (variables::iterator iterator = _variableMap->begin(); 
			iterator != _variableMap->end(); ++iterator)
		{
			cout << iterator->first << " => " << iterator->second << "\n";
		}
	}
}