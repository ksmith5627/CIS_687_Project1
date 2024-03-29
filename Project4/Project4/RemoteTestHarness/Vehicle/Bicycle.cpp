// Filename		: Bicycle.cpp
// Summary		: An implementation of the Vehicle abstract class
// Description	: Apart from implementing the methods of the Vehicle class,
//				  it also exposes a Factory method for creating an instance of itself.
//				  This factory method is called GetInstance, and it's what the TestDriver 
//				  expects when it loads the DLL.

#include "stdafx.h"
#include "Vehicle.h"
#include <string>

class __declspec(dllexport) Bicycle : public Vehicle
{
public:
	std::string ModeOfSteering();
	std::string PowerSource();
	int NumberOfWheels();
	bool LicenseRequiredToDrive();
};

inline std::string Bicycle::ModeOfSteering()
{
	return "Handlebar";
}
inline std::string Bicycle::PowerSource()
{
	return "Rider";
}
inline int Bicycle::NumberOfWheels()
{
	return 2;
}
inline bool Bicycle::LicenseRequiredToDrive()
{
	return false;
}

extern "C" __declspec(dllexport) Vehicle* GetInstance() { return new Bicycle(); }