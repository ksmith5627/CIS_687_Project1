
/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University

File Description:	CarParts.cpp : An implementation of the CarParts abstract class.

Implementation File
Details	:			Contains the implementing the methods of the CarParts class,
				    -> Exposes a Factory method for creating an instance of itself.
				    Note: This factory method is called GetInstance, and it's what the TestDriver
				    expects when it loads the DLL.
*/
/*********************************************************************************************************/

#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "string.h"
#include "CarParts.h"
#include <assert.h>
#include <iostream>

// Note these tests can be enhanced.

class __declspec(dllexport) Cycle : public CarParts
{
public:
	std::string ModeOfSteering();
	std::string PowerSource();
	int NumberOfWheels();
	bool LicenseRequiredToDrive();
};

inline std::string Cycle::ModeOfSteering(){
	return "Handle"; }

inline std::string Cycle::PowerSource(){
	return "BikeRider"; }

inline int Cycle::NumberOfWheels(){
	return 4; }

inline bool Cycle::LicenseRequiredToDrive(){
	return false; }

extern "C" __declspec(dllexport) CarParts * GetInstance() { return new Cycle(); }
