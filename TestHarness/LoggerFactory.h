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

#ifndef LOG_FACTORY_H
#define LOG_FACTORY_H
#endif 

#include "Logger.h"

class LoggerFactory
{
public:
	// Have a static function return a Logger instance.
	static BasicLogger* GetLoggerInstance(int, string, string, LogLevel, 
		bool = false, string* = nullptr, 
		std::exception* = nullptr, variables* = nullptr, bool = false);
};
