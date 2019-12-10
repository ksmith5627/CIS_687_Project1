
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 3
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/

//////////////////////////////////////////////////////////////////////
// Hexagon.cpp - An implementation of the Shape abstract class		//
// ver 1.0															//
//////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* ------------------
* it also exposes a Factory method for creating an instance of itself.
* This factory method is called GetInstance, and it's what the TestDriver
* expects when it loads the DLL.
*
* Required Files
* Shape.h
*/


#include "stdafx.h"
#include "Shape.h"
#include <cmath>

class __declspec(dllexport) RegularHexagon : public Shape
{
public:
	virtual ~RegularHexagon() {}
	double Area() {
		return 3 * std::sqrt(3) * pow(_lengthOfSide,2) / 2;
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
private:
	double _lengthOfSide = 0;
};

extern "C" __declspec(dllexport) Shape* GetInstance() { return new RegularHexagon(); }