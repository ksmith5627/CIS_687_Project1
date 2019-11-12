/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/
// Filename		: Bicycle.cpp
// Summary		: An implementation of the Vehicle abstract class
// Description	: Apart from implementing the methods of the Vehicle class,
//				  it also exposes a Factory method for creating an instance of itself.
//				  This factory method is called GetInstance, and it's what the TestDriver 
//				  expects when it loads the DLL.

#include "stdafx.h"
#include "Vehicle.h"
#include "..\Test\Test.h"
#include <string>

class __declspec(dllexport) Bicycle : public Vehicle, public ITest
{
public:
	std::string ModeOfSteering();
	std::string PowerSource();
	int NumberOfWheels();
	bool LicenseRequiredToDrive();
	bool Test();
};

inline std::string Bicycle::ModeOfSteering()
{
	return "Handlebar";
}
inline std::string Bicycle::PowerSource()
{
	return "Rider";
}
inline int Bicycle::NumberOfWheels()
{
	return 2;
}
inline bool Bicycle::LicenseRequiredToDrive()
{
	return false;
}

inline bool Bicycle::Test()
{
	if (ModeOfSteering().compare("Handlebar") == 0 && !(NumberOfWheels() == 2))
		return false;
	if (PowerSource().compare("Rider") == 0 && LicenseRequiredToDrive())
		return false;
}

extern "C" __declspec(dllexport) Bicycle* GetInstance() { return new Bicycle(); }