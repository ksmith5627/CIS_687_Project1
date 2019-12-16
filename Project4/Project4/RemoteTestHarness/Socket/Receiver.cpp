
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 4
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/

/////////////////////////////////////////////////////////////////////////////
// Receiver.cpp - A class that receives messages on a socket, and queues it//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Receiver.h"

using namespace Sockets;

// Initialize listener
Receiver::Receiver(size_t port) : _listener(port) {}

// Stop the listener
void Receiver::Stop()
{
	_listener.Stop();
}

// DeQueue from the blocking queue
Message Receiver::CollectMessage()
{
	return _receiveQueue.DeQueue();
}

// Return a pointer to the blocking queue
BlockingQueue<Message>* Receiver::GetQueue()
{
	return &_receiveQueue;
}