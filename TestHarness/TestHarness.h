
/*********************************************************************************************************/
/*
Team Members:		 Julia Thee, Derek Janzen and Kenneth Smith
Course:				 CIS 687 -  Object Oriented Design
Assignment:			 CIS 687 Homework 1
Instructor:			 Professor Scott Roueche

					 College of Engineering & Computer Science
					 Syracuse University

Program Focus:   	 The purpose of this program is to test functions using a created test harness.
					 The user can run the program within the Visual Studio IDE and the test output will be written
					 to the generated console window.

File Description:	 This header file (with the extension .h) contains class definitions and functions.

					 The user invoke tests and the results will be passed to the consol window

Header File Details: Header files contain definitions of Functions and Variables, which is imported or
					 used into any C++ program by using the pre-processor #include statement. Header file
					 have an extension ".h" which contains C++ function declaration and macro definition.

					 Each header file contains information (or declarations) for a particular group of
					 functions. Like stdio.h header file contains declarations of standard input and output
					 functions available in C++ which is used for get the input and print the output.
					 Similarly, the header file math.h contains declarations of mathematical functions
					 available in C++.
*/
/*********************************************************************************************************/

#pragma once

#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H
#endif

#include <map>
#include <typeinfo>
#include "Logger.h"
#include "LoggerFactory.h"

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
		// The declaration for logger could've been prior to the try block, 
		// and the call to LogMessage() after the catch block
		// While in this catch block a pointed to the exception is passed.
		// Note: We are unable to call LogMessage() outside the catch block
		// because the exception will be out of scope.
		try
		{
			// Invoke the test
			auto returnValue = t();
			
			// Initialize logger w/ results of test
			BasicLogger* logger = _loggerFactory.GetLoggerInstance(++_testSequence, testName, 
				typeid(t).name(), _logLevel, (bool)returnValue, message, nullptr, variableMap, _includeDateTime);
			
			// Log the message.
			logger->LogMessage();
		}
		// Here we are catching the excedption where somthing has gone wrong!
		catch (std::exception &e)
		{
			// Initialize logger with exception and set result to false
			BasicLogger* logger = _loggerFactory.GetLoggerInstance(++_testSequence, testName, 
				typeid(t).name(), _logLevel, false, message, &e, variableMap, _includeDateTime);
			
			// Log the message.
			logger->LogMessage();
		}
	}

	// Execute a sequence of tests in the order passed
	// 1. Log the test name and the result
	template <typename Test, typename... Tests>
	void ExecuteTest(string testName, Test& t, Tests&... ts)
	{
		ExecuteTest(testName, t);
		ExecuteTest(testName, ts...);
	}

	// Execute a sequence of tests one after the other, in the order passed
	// 1. Log the test name, 
	// 2. Log the result, 
	// 3. And log any additionally a message(s)
	template <typename Test, typename... Tests>
	void ExecuteTest(string testName, string* message, Test& t, Tests&... ts)
	{
		ExecuteTest(testName, message, t);
		ExecuteTest(testName, message, ts...);
	}

	// Execute a sequence of tests one after the other, in the order passed
	// 1. Log the test name
	// 2. Log the result
	// 3. Log a message and any additionally a list of variable names and their values
	template <typename Test, typename... Tests>
	void ExecuteTest(string testName, string* message, variables* variableMap, Test& t, Tests&... ts)
	{
		ExecuteTest(testName, message, variableMap, t);
		ExecuteTest(testName, message, variableMap, ts...);
	}

	// Rest -> test sequence back to a value of zero.
	void ResetTestSequence();

	// Change the log level to a new value
	// Note bool =  false
	void UpdateLogLevel(LogLevel, bool = false);

	// Declare variables 
private:
	LogLevel _logLevel;
	bool _includeDateTime;
	static LoggerFactory _loggerFactory;
	int _testSequence;
};