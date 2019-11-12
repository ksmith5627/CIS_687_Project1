
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/

// Filename		: Vehicle.h
// Summary		: Defines an abstract class for a vehicle. 
// Description	: This is an abstract class for a vehicle. It's implemented by another class, 
//				  Bicycle, that is then used by TestDriver to test against. It's also referenced
//				  by the TestDriver so it has an idea of the interface that it's calling, without
//				  worrying about the implementation.


#pragma once

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle
{
public:
	virtual ~Vehicle() {}
	virtual std::string ModeOfSteering() = 0;
	virtual std::string PowerSource() = 0;
	virtual bool LicenseRequiredToDrive() = 0;
	virtual int NumberOfWheels() = 0;
};

#endif // !VEHICLE_H

