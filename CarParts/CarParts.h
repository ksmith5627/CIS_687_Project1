
/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University

File Description:	CarParts.h : Defines an abstract class for this test DLL.

Implementation File
Details:			This is an abstract class for thr test DLL that is implemented by the implementation class
				    CarParts.c which is then used by TestDriver to invoke test against. This is also referenced
				    by the TestDriver so it has an idea of the interface that it's calling, without
				    caring about the implementation.
*/
/*********************************************************************************************************/

#pragma once

#ifndef CARPARTS_H
#define CARPARTS_H

#include <string>

class CarParts
{
public:
	virtual ~CarParts() {}
	virtual std::string ModeOfSteering() = 0;
	virtual std::string PowerSource() = 0;
	virtual bool LicenseRequiredToDrive() = 0;
	virtual int NumberOfWheels() = 0;
};

#endif 