
/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University

File Description:	TestInterface.h : Defines an abstract class for a ITest. 

Implementation File
Details:			This is an abstract class, ITest, that contains the method that returns a bool value
                    and takes no arguments per lab project requirements.

					1. Contains a method called LoadDLL, which will load the DLLs that each
				       TestDriver to test. 
					2. Note: The list of DLLs is passed to the main EXECUTIVE package upon startup. Therefore the 
					   TestDriver and its dependencies cannot be loaded in one pass.
*/
/*********************************************************************************************************/

// Lab Requirement: TestDrivers shall implement an ITest interface1 that declares a test method taking no arguments 
// and returning a boolean value indicating test pass or failure.
#pragma once

#ifndef TESTINTERFACE_H
#define TESTINTERFACE_H

class ITest
{
public:
	virtual ~ITest() {}
	virtual bool Test() = 0;
	virtual void LoadDLL(const char*, const char*) = 0;
};

#endif
