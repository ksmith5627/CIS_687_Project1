#include "stdafx.h"
#include "Endpoint.h"
#include "..\Utilities\converter.h"
#include <iostream>
#include <exception>

using namespace Sockets;

// Default constructor
EndPoint::EndPoint() {}

// Copy constructor
EndPoint::EndPoint(const EndPoint& endPoint)
{
	_address = endPoint.GetUriHost();
	_port = endPoint.GetPort();
}

// Assignment operator
void EndPoint::operator=(const EndPoint& endPoint)
{
	_address = endPoint.GetUriHost();
	_port = endPoint.GetPort();
}

// Constructor from a string representation of an endpoint
EndPoint::EndPoint(const std::string& address)
{
	size_t index = address.find_first_of(SEPARATOR);
	if (index == address.length())
		throw new std::exception("No port number specified while initiating endpoint");
	_address = address.substr(0, index);
	_port = Convert::FromString<size_t>(address.substr(index + 1));
}

// Return string representation of endpoint
std::string EndPoint::AsString()
{
	return _address + ":" + Convert::ToString(_port);
}

// Return the hostname
std::string EndPoint::GetUriHost() const
{
	return _address;
}

// Return the port number
size_t EndPoint::GetPort() const
{
	return _port;
}