/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University

File Description:	ShapesAndSides.h : Defines an abstract class for calculating sides for types of shapes. 

Implementation File
Details:			This is an abstract class is an implemented by another class, 
				    that is then used by TestDriver to test against. It's also referenced
				    by the TestDriver so it has an idea of the interface that it's calling, without
				    caring about the implementation.
*/
/*********************************************************************************************************/

#pragma once

#ifndef SHAPESANDSIDES_H
#define SHAPESANDSIDES_H

class ShapesAndSides
{
public:
	virtual ~ShapesAndSides() {}
	virtual double Area() = 0;
	virtual double Perimeter() = 0;
	virtual int NumberOfSides() = 0;
	virtual void SetLengthOfSide(double) = 0;
};

#endif 