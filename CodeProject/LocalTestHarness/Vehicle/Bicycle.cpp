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

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

class __declspec(dllexport) Bicycle : public Vehicle, public ITest
{
public:
	virtual ~Bicycle() {}
	//std::string ModeOfSteering();
	//std::string PowerSource();
	int NumberOfWheels();
	bool LicenseRequiredToDrive();
	//bool Test();
	int Test();
};

int Bicycle::NumberOfWheels()
{
	return 2;
}
bool Bicycle::LicenseRequiredToDrive()
{
	return false;
}

//bool Bicycle::Test()
int Bicycle::Test()
{
	return 3;

	//if (ModeOfSteering().compare("Handlebar") == 0 && !(NumberOfWheels() == 2))
	/*
	if (!(NumberOfWheels() == 2))
		return false;
	//if (PowerSource().compare("Rider") == 0 && LicenseRequiredToDrive())
	if (LicenseRequiredToDrive())
		return false;
	*/
}


extern "C" __declspec(dllexport) Bicycle* GetInstance() { return new Bicycle(); }