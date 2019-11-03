/*********************************************************************************************************/
/*
Team Members:		 Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
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

#ifndef LOGGER_H
#define LOGGER_H
#endif 

#include <iostream>
#include <map>

// Provide aliases for commonly used types that make the code look long
using string = std::string;
using variables = std::map<string, string>;

// Conmfigure the different support log levels
enum LogLevel { 
				BASIC, 
				DETAILED, 
				VERBOSE 
			  };

// Define the Basic logger class
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

// The DetailedLogger class:
// 1. Prints exception info in case of failures
// 2. Overrides the base class LogMessage() to add its own implementation
// Note: The following is derived from BasicLogger
class DetailedLogger : public BasicLogger
{
	public:
		DetailedLogger(int, string, string, bool = false, string* = nullptr, std::exception* = nullptr);
		virtual void LogMessage();
		virtual ~DetailedLogger();

	private:
		string *_message;				// message to be printed with the test result
		std::exception * _exception;	// exception whose details have printed in case of test failure 
										// caused by an unhandled exception.
};

// The VerboseLogger, which additionally prints a list of variables
// overrides the base class LogMessage() to add its own implementation
// It also optionally prints the timestamp denoting the time the test was run/
// It derives from DetailedLogger
class VerboseLogger : public DetailedLogger
{
public:
	VerboseLogger(int, string, string, bool = false, string* = nullptr, 
		std::exception* = nullptr, variables* = nullptr, bool = false);
	virtual void LogMessage();
	virtual ~VerboseLogger();

private:
	bool _includeDateTime;		// Flag denoting whether or not the timestamp must be printed
	variables* _variableMap;	// A map of variable names and their values to be printed
};