
/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 3
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

Team Update:  New code has been added to support the loading of DLL's from an XML 

Team Update: Update for HW #3 -  Updating the code to implement ITest within each DLL

*/
/*********************************************************************************************************/

// Program.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <functional>
#include <iostream>
#include "MathLibrary.h"		   // 1st DLL
#include "../ArithmeticTestLibrary/ArithmeticTestLibrary.h" // 2nd DLL

#include "TestObject.h" // added for Deserialzation and Parsing
#include <windows.h>
//#include "Test.h"  // add to check for parsing  (Below a new ITest added)
#include "../TestInterface/TestInterface.h" // 2nd DLL
#include <list> // added to hold list values

#include <chrono>
#include <ctime>
#include <iomanip>

using std::cout;
using std::endl;
using namespace std;

typedef ITest* (__stdcall* TestDriverInstance)(); 

// The following code is used for testing the loading of the DLL's
// DLL #1
typedef double (*funcAdd)(double, double);
typedef double (*funcMult)(double, double);

// DLL #2
typedef int (*func_additionTest)(int, int);
typedef int (*func_subtractionTest)(int, int);
typedef int (*func_SuccessfulDivisionTest)(int, int);
typedef bool (*func_FailedDivisionTest);

void ProcessTestObject(TestObject testObj); // declared the function 
void ProcessTestObject2_ManualLoadingOfDLL(TestObject testObj); // declared the function 
string GetFilenameWithoutExtension(string filename); // define function
void ShowTestResult(TestObject testObj, bool result); // define function

#pragma region Homework_1

//// Test class that overrides () 
//// Test the passing a func. to furtherrthe TestHarness
//class TestACar
//{
//	private:
//		int _wheels;
//
//	public:
//		TestACar(int wheels = 4): _wheels(wheels)
//		{
//
//		}
//		bool operator()()
//		{
//			return _wheels == 4;
//		}
//};
//
//// Function that throws an exception in a given case(s)
//// Test the exception handling of this TestHarness
//int division(int a, int b)
//{
//	if (b == 0)
//		throw std::exception("Division by zero attempted");
//	return a / b;
//}
//
//// Below Random Functions
///***********************************/
///***********************************/
//inline int addition(int a, int b)
//{
//	return a + b;
//}
//
//inline int subtraction(int a, int b)
//{
//	return a - b;
//}
//
//// Outcome: This is a test that is guaranteed to fail
//bool FailedDivision()
//{
//	return division(5, 0) == 1;
//}
//
//// Outcome: This is a test that is guaranteed to pass
//bool SuccessfulDivision()
//{
//	return division(6, 3) == 2;
//}
//
//// Outcome: These tests will pass
//bool Addition()
//{
//	return addition(5, 3) == 8;
//}
//
//bool Subtraction()
//{
//	return subtraction(10, 7) == 3;
//}
///***********************************/
///***********************************/
//#pragma endregion Homework_1


int main()
{
//#pragma region Homework_1
//	   
//	// Create a TestHarness object.
//	TestHarness runTest;
//
//	// #1 Invoke a test
//	// Execute sequence of tests, where all succeed
//	runTest.ExecuteTest("Successful__TestSuite", SuccessfulDivision, Addition, Subtraction);
//	cout << endl;
//
//	// Reset the test sequence 
//	// so they're numbered starting from 1.
//	runTest.ResetTestSequence();
//
//	// Update the loglevel to DETAILED
//	runTest.UpdateLogLevel(DETAILED);
//
//	// #2 Invoke a test
//	// Execute tests, one at a time.
//	string message = "Calculate the value of infinity";
//	runTest.ExecuteTest("Failed__DivisionTest", &message, FailedDivision);
//	cout << endl;
//
//	// Lets invoke a tes and use VERBOSE logging
//	runTest.UpdateLogLevel(VERBOSE);
//
//	variables variableMap = variables();
//	variableMap["a"] = "6";
//	variableMap["b"] = "3";
//	variableMap["quotient"] = "2";
//
//	// #3 Invoke a test
//	runTest.ExecuteTest("Successful__DivisionTest", nullptr, &variableMap, SuccessfulDivision);
//	cout << endl;
//
//	runTest.ResetTestSequence();
//
//	// Now lets see the VERBOSE logging by setting the flag to include timestamp.
//	runTest.UpdateLogLevel(VERBOSE, true);
//
//	// Create an object of Car that can act as a functor
//	TestACar test_car(4);
//
//	// Create a lambda expression so we can test whether the TestHarness can handle it.
//	auto lambda = [&]() { return addition(5, 2) == 8; };
//
//	// #4 Invoke a test
//	// Execute sequence of tests, that's a mix of function pointers, functors & lambda expressions.
//	runTest.ExecuteTest("Failed__TestSuite", FailedDivision, Addition, Subtraction, lambda, test_car);
//
//#pragma endregion Homework_1
//	
//#pragma region Homework_2_TeamTestSampleCode
//
//	/*******************************************/
//	// START OF DLL IMPLEMENTATON -  Microsoft
//	// The following implementation is from:
//	// https://docs.microsoft.com/en-us/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=vs-2019
//	/*******************************************/
//
//	std::cout << " " << std::endl;
//	std::cout << "Start of Windows Dev Studio Test code " << std::endl;
//
//	// Initialize a Fibonacci relation sequence.
//	fibonacci_init(1, 1);
//	// Write out the sequence values until overflow.
//	do {
//		std::cout << fibonacci_index() << ": "
//			<< fibonacci_current() << std::endl;
//	} while (fibonacci_next());
//	// Report count of values written before overflow.
//	std::cout << fibonacci_index() + 1 <<
//		" Fibonacci sequence values fit in an " <<
//		"unsigned 64-bit integer." << std::endl;
//
//	/*******************************************/
//	// END OF DLL IMPLEMENTATON -  Microsoft
//	/*******************************************/
//	
//	/*******************************************/
//	// START OF PROF CODE FROM CLASS 
//	// Using Microsoft Properties
//	/*******************************************/
//	cout << " " << endl;
//	cout << "Start of Prof Test code " << std::endl;
//		if (Add != NULL) {
//			cout << "10 + 10 = " << Add(10, 10) << std::endl;
//		}
//		else
//			cout << "Did not load Add correctly." << std::endl;
//		if (Multiply != NULL) {
//			cout << "50 * 10 = " << Multiply(50, 10) << std::endl;
//		}		
//	//std::cin.get();
//	/*******************************************/
//	// END OF PROF CODE FROM CLASS
//	// Using Microsoft Properties
//	/*******************************************/		
//		
//
//	/*******************************************/
//	// START OF PROF CODE FROM CLASS 
//	// Using the Profesors code from class 
//	/*******************************************/
//	
//	/* Done to test the loading of the DLL
//       Note the following code below can be used to also load the DLL
//	   Now we can just parse the XML file to invoke the DLL
//    */
//		HINSTANCE hDLL;
//		funcAdd Add;
//		funcMult Multiply;
//		
//		//const wchar_t* libName = L"MathLibrary";
//		LPCSTR libName = "MathLibrary";
//
//		hDLL = LoadLibraryEx(libName, NULL, NULL);   // Handle to DLL
//
//		if (hDLL != NULL) {
//			Add = (funcAdd)GetProcAddress(hDLL, "Add");
//			Multiply = (funcMult)GetProcAddress(hDLL, "Multiply");
//			if (Add != NULL) {
//				std::cout << "10 + 10 = " << Add(10, 10) << std::endl;
//			}
//			else
//				std::cout << "Did not load Add correctly." << std::endl;
//			if (Multiply != NULL) {
//				std::cout << "50 * 10 = " << Multiply(50, 10) << std::endl;
//			}
//			else
//				std::cout << "Did not load Multiply correctly." << std::endl;
//			FreeLibrary(hDLL);
//		}
//		else {
//			std::cout << "Library load failed!" << std::endl;
//		}
//	
//	/*******************************************/
//	// END OF PROF CODE FROM CLASS 
//	// Using the Profesors code from class 
//	/*******************************************/
    
	/*******************************************/
	// START OF TEAM HOMEWORK #2  - Sample Test Code
	// Parsing XML and loading DLL's to run test
	/*******************************************/
	
	// #1 The following is done to test the parsing 
	// and loading of the created DLL
//	list<TestObject> testObjects = TestObject::DeserializeXml("TestRequest.xml");
//	for (auto const& iterator : testObjects) {
//		ProcessTestObject(iterator);
//	}
//	
//	// #2 The following will parse an XML and load DLL 
//	//    to invoke the DLL's function for testing 
//	// Note:  The ArithmeticTestLibrary.DLL is loaded manually (in code)
//	list<TestObject> testObjects2 = TestObject::DeserializeXml("TestRequest2.xml");
//	for (auto const& iterator : testObjects2) {
//		ProcessTestObject2_ManualLoadingOfDLL(iterator);
//	}
//
//	/*******************************************/
//	// START OF TEAM HOMEWORK #2  - Sample Test Code
//	// Parsing XML and loading DLL's to run test
//	/*******************************************/
//
//#pragma endregion Homework_2_TeamTestSampleCode

	/*******************************************/
	// START OF TEAM HOMEWORK #2  
	// Parsing XML and Interface to loading DLL's 
	// and run tests
	/*******************************************/
	list<TestObject> testObjects3 = TestObject::DeserializeXml("TestHW2.xml");
	for (auto const& iterator : testObjects3) {
		ProcessTestObject(iterator);
	}

	return 0;
}


// ksnote - change the commentr below!!!!

// Executes a single test object
// This is where the magic happens, so to speak.
// The test driver is loaded, and an object of TestDriver
// is created using the Factory "GetTestInstance" method.
// It then uses the object to load the "TestedCodes" libraries.
// Once done, it invokes the Test() function, and passes the baton
// on to PrintTestResult()
void ProcessTestObject(TestObject testObj)
{

	HINSTANCE testInstance = LoadLibrary(testObj.GetTestDriver().c_str());
		if (testInstance == nullptr)
		{
			cout << "Failure loading library " << testObj.GetTestDriver() << endl;
			return;
		}

		TestDriverInstance tdInstance = (TestDriverInstance)GetProcAddress(testInstance, "GetTestInstance");
		if (tdInstance == nullptr)
		{
			cout << "Failure running GetProcAddress on function GetTestInstance" << endl;
			return;
		}

		for (auto const& iterator : testObj.GetTestedCodes()) {
			iterator.c_str();
		}

		// The following code below could be used		
		ITest* test = tdInstance();
		for (auto const& iterator : testObj.GetTestedCodes())
		{
			test->LoadDLL(GetFilenameWithoutExtension(iterator).c_str(), iterator.c_str());
		}

		ShowTestResult(testObj, test->Test());
		
}

//// This function will parse an XML and manually load a test DLL
//void ProcessTestObject2_ManualLoadingOfDLL(TestObject testObj)
//{
//	string a = " ";
//	string b = " ";
//
//	HINSTANCE hDLL;
//	func_additionTest Add;
//	func_subtractionTest Multiply;
//	func_SuccessfulDivisionTest Divide;
//	func_FailedDivisionTest FailedDivide;
//	
//	LPCSTR libName = "ArithmeticTestLibrary";
//
//	hDLL = LoadLibraryEx(libName, NULL, NULL);  // Handle to DLL
//
//	if (hDLL != NULL) {
//		Add = (func_additionTest)GetProcAddress(hDLL, "additionTest");
//		Multiply = (func_subtractionTest)GetProcAddress(hDLL, "subtractionTest");
//		Divide = (func_SuccessfulDivisionTest)GetProcAddress(hDLL, "SuccessfulDivisionTest");
//		FailedDivide = (func_FailedDivisionTest)GetProcAddress(hDLL, "FailedDivisionTest");
//
//		if (Add != NULL) {
//			std::cout << "10 + 10 = " << Add(10, 10) << std::endl;
//		}
//		else
//			std::cout << "Did not load Add correctly." << std::endl;
//		if (Multiply != NULL) {
//			std::cout << "50 * 10 = " << Multiply(50, 10) << std::endl;
//		}
//		else
//			std::cout << "Did not load Multiply correctly." << std::endl;
//		if (FailedDivide != NULL) {
//			std::cout << "Returned false = " << FailedDivide << std::endl;
//		}
//		else
//			std::cout << "Did not load FailedDivide correctly." << std::endl;
//		if (Divide != NULL) {
//			std::cout << "50 * 10 = " << Divide(50, 10) << std::endl;
//		}
//		else
//			std::cout << "Did not load Divide correctly." << std::endl;
//				
//		// The following section will retrieve the TestCode values to invoke an of 
//		// of the loaded test functions.
//		list<string> theList;
//
//		for (auto const& iterator : testObj.GetTestedCodes()) {
//			const char* value = iterator.c_str();
//			string value2 = iterator.c_str();
//
//			//3.2 Position the Iterator for Insertion
//			list<string>::iterator Position;
//			Position = theList.begin();
//			theList.insert(Position, 1, value2);
//
//			//3.3 Insert an element and print the list
//			cout << "Inserting the Single Element" << endl;
//			cout << endl;
//		}
//		
//		cout << endl;
//		cout << "Popping out the elements in mylist:";
//		while (!theList.empty())
//		{
//			// first list value
//			cout << ' ' << theList.front();
//			a = theList.front();
//			theList.pop_front();
//
//			// second list value
//			cout << ' ' << theList.back();
//			b = theList.back();
//			theList.pop_back();
//		}
//
//		int i = std::atoi(a.c_str());
//		int j = std::atoi(b.c_str());
//
//		if (Add != NULL) {
//			
//			cout << endl;
//			cout << "Here we are using input from the XML " << Add(i, j) << std::endl;
//		}
//					   		 
//		FreeLibrary(hDLL);
//	}
//	else {
//		cout << "Library load failed!" << std::endl;
//	}
//
//}

string GetFilenameWithoutExtension(string filename)
{
	size_t index = filename.find_last_of("\\/");
	if (index != string::npos)
	{
		filename.erase(0, index + 1);
	}

	index = filename.rfind('.');
	if (index != string::npos)
	{
		filename.erase(index);
	}

	return filename;
}

// 1. Prints the test result, current timestamp
// 2. Prints the TestDriver & TestedCodes used to execute the test
// 3. Prints the status of the test
void ShowTestResult(TestObject testObj, bool result)
{
	auto now = chrono::system_clock::now();
	auto now_c = chrono::system_clock::to_time_t(now);

	cout << endl; 
	cout << endl;
	cout << "Team test Homework #2 Results" << endl;
	cout << "[" << std::put_time(std::localtime(&now_c), "%c") << "] " << endl;
	cout << "Test using driver " << testObj.GetTestDriver() << " and tested codes ( ";
	for (auto const& iterator : testObj.GetTestedCodes())
	{
		cout << iterator << " ";
	}
	cout << ") was " << (result ? "successful" : "unsuccessful") << endl;
}
