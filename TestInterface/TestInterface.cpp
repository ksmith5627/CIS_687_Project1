/*********************************************************************************************************/
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 2
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University

File Description:	TestInterface.cpp : ITest abstract class

Implementation File
Details:			The factory will 'return' an instance of the proper and expected logger based LogLevel

					1. Implementing the methods of the ITest class.
					2. Exposes a Factory method for creating an instance of itself.
					3. The TestDriver expect the factory method named GetInstance when it loads the DLL.
*/
/*********************************************************************************************************/
// Development Note:
// The test DLL's must be available because the output of the test function depends on it.
// An instance of the test DLL's are loaded and those objects are used to run some the created tests.

// Note: Test DLL's when created must be added to this fil
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "..\CarParts\CarParts.h"
#include "..\ShapesAndSides\ShapesAndSides.h"
#include "string.h"
#include <assert.h>
#include "TestInterface.h"
#include <exception>
#include <iostream>
#include <list>

using std::cout;
using std::endl;
using namespace std;

// Here add the typeddef declarations for new DLLs
typedef CarParts* (CALLBACK* CarPartsInstance)();
typedef ShapesAndSides*(CALLBACK *ShapesAndSidesInstance)();

//typedef Shape* (CALLBACK* ShapeInstance)();

/// Class defintion 
class __declspec(dllexport) TestDriver : ITest
{
	public:
		virtual ~TestDriver();
		bool Test();  // This executes the boolean tests 
		void LoadDLL(const char*, const char*);
	private:
		FARPROC GetInstanceFromDLL(const char*);  
		//FARPROC GetInstanceFromDLL(const wchar_t*);
		CarParts* _nutsAndBolts;
		ShapesAndSides* _shapeOfSide;
		list<HMODULE> _modules;
};

// extern test driver declaration
extern "C" __declspec(dllexport) TestDriver * GetTestInstance() { return new TestDriver(); }

// Note: The following code is almost identical to the original test code 
//       in Program.cpp.  Here for the test driver the test DLL's are expected

// Free up any DLLs loaded when the object goes out of scope
TestDriver::~TestDriver()
{
	for (auto const& iterator : _modules)
		FreeModule(iterator);
}

// Load any DLLs the test driver depends on.
// This instance depends on Vehicle.dll & Shape.dll
//void TestDriver::LoadDLL(const char* name, const char* path)
void TestDriver::LoadDLL(const char* name, const char* path)
{
	if (strcmp(name, "CarParts") == 0)
	{
		CarPartsInstance vInstance = 
			(CarPartsInstance)(GetInstanceFromDLL((path)));
		if (vInstance == nullptr)
			throw new std::exception("Error initializing CarParts Instance. Couldn't find GetInstance method");
		_nutsAndBolts = vInstance();
	}

	if (strcmp(name, "ShapesAndSides") == 0)
	{
		ShapesAndSidesInstance sInstance = 
			(ShapesAndSidesInstance)(GetInstanceFromDLL((path)));
		if (sInstance == nullptr)
			throw new std::exception("Error initializing ShapesAndSidesInstance. Couldn't find GetInstance method");

		_shapeOfSide = sInstance();
	}
}

// Once the DLLs are loaded, it creates an object of each class.
// And uses them to run some tests that should always pass.
bool TestDriver::Test()
{
	//if (_nutsAndBolts == nullptr)
	if (_nutsAndBolts == nullptr || _shapeOfSide == nullptr) // condition check
		throw new std::exception("Test() called without loading the DLLs required");

	if (_nutsAndBolts->ModeOfSteering().compare("Handle") == 0 && !(_nutsAndBolts->NumberOfWheels() == 4))
		return false;
	if (_nutsAndBolts->PowerSource().compare("BikeRider") == 0 && _nutsAndBolts->LicenseRequiredToDrive())
		return false;
	
	_shapeOfSide->SetLengthOfSide(6);

	if (_shapeOfSide->Perimeter() > 6 * 
		_shapeOfSide->NumberOfSides())
		return false;

	if (_shapeOfSide->Area() < 54)
		return false;
	
	return true;
}

/* 
	Given a DLL path, it loads it into memory then returns a 
	function pointer to the Factory method "GetInstance".
	This is a method that is used by the LoadDLL function.
*/
FARPROC TestDriver::GetInstanceFromDLL(const char* dllPath)
//FARPROC TestDriver::GetInstanceFromDLL(const wchar_t* dllPath)
{
	HMODULE module = LoadLibrary(dllPath);
	if (module != nullptr)
	{
		_modules.push_back(module);
		return GetProcAddress(module, "GetInstance");
	}
	return nullptr;
}
