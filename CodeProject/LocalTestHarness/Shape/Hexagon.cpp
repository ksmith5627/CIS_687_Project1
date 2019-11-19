/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/
// Filename		: Hexagon.cpp
// Summary		: An implementation of the Shape abstract class
// Description	: Apart from implementing the methods of the Shape class,
//				  it also exposes a Factory method for creating an instance of itself.
//				  This factory method is called GetInstance, and it's what the TestDriver 
//				  expects when it loads the DLL.


#include "stdafx.h"
#include "Shape.h"
#include "..\Test\Test.h"
#include <cmath>

#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

class __declspec(dllexport) RegularHexagon : public Shape, public ITest
{
public:
	virtual ~RegularHexagon() {}
	double Area() {
		return 3 * std::sqrt(3) * pow(_lengthOfSide, 2) / 2;
	}
	double Perimeter() {
		return _lengthOfSide * NumberOfSides();
	}
	int NumberOfSides() {
		return 6;
	}
	void SetLengthOfSide(double length)
	{
		_lengthOfSide = length;
	}

	bool Test()
	{	
		SetLengthOfSide(6);

		if (Perimeter() > 6 * NumberOfSides())
			return false;

		if (Area() < 54)
			return false;
	}

private:
	double _lengthOfSide = 0;
};

extern "C" __declspec(dllexport) ITest* GetInstance() { return new RegularHexagon(); }