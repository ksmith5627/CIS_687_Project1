/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/
// Filename		: LocalTestHarness.cpp
// Summary		: Defines the entry point for the console application.
// Description	: This is the Executive package, so to speak. The TestRequest XML path
//				  is hard-coded into the program. It parses the XML, serializes it to a 
//				  list of TestObject objects, and for each of the objects, Loads the 
//				  appropriate DLLs, invokes the test() method, and prints the results.

#include "stdafx.h"
#include "TestObject.h"
#include "Test\Test.h"
#include <windows.h>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

typedef ITest*(__stdcall* TestDriverInstance)();

// Strip the path and the extension from a file.
// So if you pass C:\foo\bar.txt, you'd just get back
// "bar"

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

// Prints the test result.
// Prints the current timestamp
// Then prints the TestDriver & TestedCodes used to execute the test
// followed by the status of the test
void PrintTestResult(std::string testObject, bool result)
{
	auto now = chrono::system_clock::now();
	auto now_c = chrono::system_clock::to_time_t(now);
	std::cout << "[" << std::put_time(std::localtime(&now_c), "%c") << "] ";

	cout << "Test using the following DLLs ( " << testObject << ") was " << (result ? "successful" : "unsuccessful") << endl;
}

// Executes a single test object
// This is where the magic happens, so to speak.
// The test driver is loaded, and an object of TestDriver
// is created using the Factory "GetTestInstance" method.
// It then uses the object to load the "TestedCodes" libraries.
// Once done, it invokes the Test() function, and passes the baton
// on to PrintTestResult()
void ProcessTestObject(TestObject testObj)
{
	for (auto const& iterator : testObj.GetTestDrivers())
	{
		HINSTANCE testInstance = LoadLibrary(iterator.c_str());
		if (testInstance == nullptr)
		{
			cout << "Failure loading library " << iterator << endl;
			continue;
		}

		TestDriverInstance tdInstance = (TestDriverInstance)GetProcAddress(testInstance, "GetInstance");
		if (tdInstance == nullptr)
		{
			cout << "Failure running GetProcAddress on function GetTestInstance" << endl;
			return;
		}

		ITest* test = tdInstance();
		test->Test();
		//PrintTestResult(iterator, test->Test());
	}
}

// Parse the input XML, call ProcessTestObject on each of them
int main()
{
	TestObject testObject = TestObject::DeserializeXml("TestRequest.xml");
	ProcessTestObject(testObject);
    return 0;
}

