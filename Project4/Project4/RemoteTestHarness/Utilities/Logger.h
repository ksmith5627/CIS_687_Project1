#pragma once

/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 4
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/
////////////////////////////////////////////////////////////////////////////
// Logger.h - A class that exposes a thread safe console logger function  //
////////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package contains a single static function to log
* messages to the console.
* 
*/

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <mutex>

namespace Utilities
{
	static std::mutex _mutex;
	class Logger
	{
	public:
		static void inline Log(const char* message, bool newline = true)
		{
			std::lock_guard<std::mutex> lock(_mutex);
			std::cout << message;
			if (newline)
				std::cout << std::endl;
		}

	};
}

#endif // !LOGGER_H