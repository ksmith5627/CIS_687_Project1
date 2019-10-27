
/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen and Kenneth Smith
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

// Constructor for the TestHarness.
// logLevel defaults to BASIC & includeDateTime to false
// includeDateTime only applies if loglevel = VERBOSE
TestHarness::TestHarness(LogLevel logLevel, bool includeDateTime)
{
	UpdateLogLevel(logLevel, includeDateTime);
	ResetTestSequence();
}

// Reset the test sequence to 0.
void TestHarness::ResetTestSequence()
{
	_testSequence = 0;
}

// Updates log level, overriding what was set in the constructor.
void TestHarness::UpdateLogLevel(LogLevel logLevel, bool includeDateTime)
{
	_logLevel = logLevel;
	if (_logLevel == VERBOSE)
		_includeDateTime = includeDateTime;
}