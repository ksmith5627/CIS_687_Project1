// ArithmeticTestLibrary.h - Contains declarations of math functions
#pragma once

#ifdef ARITHMETICTESTLIBRARY_EXPORTS
#define ARITHMETICTESTLIBRARY_API __declspec(dllexport)
#else
#define ARITHMETICTESTLIBRARY_API __declspec(dllimport)
#endif

// Define function implementation
// Functions from HW #1
extern "C" ARITHMETICTESTLIBRARY_API int additionTest(int a, int b);
extern "C" ARITHMETICTESTLIBRARY_API int subtractionTest(int a, int b);
extern "C" ARITHMETICTESTLIBRARY_API int SuccessfulDivisionTest(int a, int b);
extern "C" ARITHMETICTESTLIBRARY_API bool FailedDivisionTest();