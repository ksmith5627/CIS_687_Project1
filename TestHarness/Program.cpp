
/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 1
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University

Program Focus:      The purpose of this program is to test functions using a created test harness.
					The user can run the program within the Visual Studio IDE and the test output will be written
					to the generated console window.

File Description:	Program.cpp : Defines the entry point for the console application.

Implementation File
Details:			The factory will 'return' an instance of the proper and expected logger based LogLevel

					1. The log level is determined from the passed arguments.
					2. Note: If a variable map is passed then a VerboseLogger instance is returned.
					3. Note: If message is passed the a DetailedLogger instance is returned.
					4, By default the BasicLogger instance is returned.

Function  Info:     A member function definition for a class are stored in a separate .cpp file,
					which is called the class implementation file. The file usually has the same
					name as the class, with the .cpp extension. For example the Time class member
					functions would be defined in the file Time.cpp. The file name could be simularly
					named.
*/
/*********************************************************************************************************/

// Program.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <functional>
#include <iostream>
#include "MathLibrary.h"

using std::cout;
using std::endl;

// Test class that overrides () 
// Test the passing a func. to furtherrthe TestHarness
class TestACar
{
	private:
		int _wheels;

	public:
		TestACar(int wheels = 4): _wheels(wheels)
		{

		}
		bool operator()()
		{
			return _wheels == 4;
		}
};

// Function that throws an exception in a given case(s)
// Test the exception handling of this TestHarness
int division(int a, int b)
{
	if (b == 0)
		throw std::exception("Division by zero attempted");
	return a / b;
}

// Below Random Functions
/***********************************/
/***********************************/
inline int addition(int a, int b)
{
	return a + b;
}

inline int subtraction(int a, int b)
{
	return a - b;
}

// Outcome: This is a test that is guaranteed to fail
bool FailedDivision()
{
	return division(5, 0) == 1;
}

// Outcome: This is a test that is guaranteed to pass
bool SuccessfulDivision()
{
	return division(6, 3) == 2;
}

// Outcome: These tests will pass
bool Addition()
{
	return addition(5, 3) == 8;
}

bool Subtraction()
{
	return subtraction(10, 7) == 3;
}
/***********************************/
/***********************************/

int main()
{
	// Create a TestHarness object.
	TestHarness runTest;

	// #1 Invoke a test
	// Execute sequence of tests, where all succeed
	runTest.ExecuteTest("Successful__TestSuite", SuccessfulDivision, Addition, Subtraction);
	cout << endl;

	// Reset the test sequence 
	// so they're numbered starting from 1.
	runTest.ResetTestSequence();

	// Update the loglevel to DETAILED
	runTest.UpdateLogLevel(DETAILED);

	// #2 Invoke a test
	// Execute tests, one at a time.
	string message = "Calculate the value of infinity";
	runTest.ExecuteTest("Failed__DivisionTest", &message, FailedDivision);
	cout << endl;

	// Lets invoke a tes and use VERBOSE logging
	runTest.UpdateLogLevel(VERBOSE);

	variables variableMap = variables();
	variableMap["a"] = "6";
	variableMap["b"] = "3";
	variableMap["quotient"] = "2";

	// #3 Invoke a test
	runTest.ExecuteTest("Successful__DivisionTest", nullptr, &variableMap, SuccessfulDivision);
	cout << endl;

	runTest.ResetTestSequence();

	// Now lets see the VERBOSE logging by setting the flag to include timestamp.
	runTest.UpdateLogLevel(VERBOSE, true);

	// Create an object of Car that can act as a functor
	TestACar test_car(4);

	// Create a lambda expression so we can test whether the TestHarness can handle it.
	auto lambda = [&]() { return addition(5, 2) == 8; };

	// #4 Invoke a test
	// Execute sequence of tests, that's a mix of function pointers, functors & lambda expressions.
	runTest.ExecuteTest("Failed__TestSuite", FailedDivision, Addition, Subtraction, lambda, test_car);

	// START OF DLL IMPLEMENTATON
	// ksnote -  10.28.19 Monday
	// The following implementation is from:
	// https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=vs-2019
	
	std::cout << " " << std::endl;
	std::cout << "Start of Windows Dev Studio Test code " << std::endl;

	// Initialize a Fibonacci relation sequence.
	fibonacci_init(1, 1);
	// Write out the sequence values until overflow.
	do {
		std::cout << fibonacci_index() << ": "
			<< fibonacci_current() << std::endl;
	} while (fibonacci_next());
	// Report count of values written before overflow.
	std::cout << fibonacci_index() + 1 <<
		" Fibonacci sequence values fit in an " <<
		"unsigned 64-bit integer." << std::endl;
	// END OF DLL IMPLEMENTATION

	// SRART OF PROF CODE FROM CLASS
	////////////////////
	std::cout << " " << std::endl;
	std::cout << "Start of Prof Test code " << std::endl;
		if (Add != NULL) {
			std::cout << "10 + 10 = " << Add(10, 10) << std::endl;
		}
		else
			std::cout << "Did not load Add correctly." << std::endl;
		if (Multiply != NULL) {
			std::cout << "50 * 10 = " << Multiply(50, 10) << std::endl;
		}		
	//std::cin.get();
	///////////////////
	// END OF PROF CODE FROM CLASS


	return 0;
}