#include "stdafx.h"

// Constructor for the TestHarness.
// logLevel defaults to BASIC & includeDateTime to false
// includeDateTime only applies if loglevel = VERBOSE
TestHarness::TestHarness(LogLevel logLevel, bool includeDateTime)
{
	UpdateLogLevel(logLevel, includeDateTime);
	ResetTestSequence();
}

// Reset the test sequence to 0.
void TestHarness::ResetTestSequence()
{
	_testSequence = 0;
}

// Updates log level, overriding what was set in the constructor.
void TestHarness::UpdateLogLevel(LogLevel logLevel, bool includeDateTime)
{
	_logLevel = logLevel;
	if (_logLevel == VERBOSE)
		_includeDateTime = includeDateTime;
}