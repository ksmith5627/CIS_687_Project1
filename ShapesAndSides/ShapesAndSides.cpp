

#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "ShapesAndSides.h"
#include <cmath>

class __declspec(dllexport) Triangle : public ShapesAndSides
{
public:
	virtual ~Triangle() {}
	double Area() {
		return 3 
			* std::sqrt(3) 
			* pow(_lengthOfSide, 2) / 2;
	}
	double Perimeter() {
		return _lengthOfSide 
			* NumberOfSides();
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

extern "C" __declspec(dllexport) ShapesAndSides * GetInstance() { return new Triangle(); }