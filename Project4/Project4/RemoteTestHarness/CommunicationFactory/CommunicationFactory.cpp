////////////////////////////////////////////////////////////////////////////
// CommunicationFactory.cpp - A factory class for the communication object//
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#define IN_DLL

#include "CommunicationFactory.h"
#include "..\Socket\Communication.h" 

using namespace Sockets;

DLL_DECL ICommunication* CommunicationFactory::CreateInstance(size_t port)
{
	return ICommunication::CreateInstance(port);
}