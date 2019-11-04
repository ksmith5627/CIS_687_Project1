
/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University

File Description:	ArithmeticTestLibrary.cpp : Defines the exported functions for the DLL.
*/
/*********************************************************************************************************/

#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "ArithmeticTestLibrary.h"
#include "framework.h" 

ARITHMETICTESTLIBRARY_API int additionTest(int a, int b) { return a + b; }
ARITHMETICTESTLIBRARY_API int subtractionTest(int a, int b) { return a - b; }
ARITHMETICTESTLIBRARY_API int SuccessfulDivisionTest(int a, int b) { return a / b; }
ARITHMETICTESTLIBRARY_API bool FailedDivisionTest() { return false; }