#pragma once

/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 4
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/

////////////////////////////////////////////////////////////////////////////
// Receiver.h - A class that receives messages on a socket, and queues it //
////////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package contains a Receiver class that receives messages
* on a socket and queues them up in a BlockingQueue.
*
* This is largely based on Prof. Fawcett's example code.
*
* Required Files:
* ---------------
* Message.h, Socket.h, BlockingQueue.h
*/

#ifndef RECEIVER_H
#define RECEIVER_H

#include "..\BlockingQueue\BlockingQueue.h"
#include "Message.h"
#include "Socket.h"


class Receiver
{
public:
	Receiver(size_t);
	template<typename CallableObject>
	void Start(CallableObject& co);
	void Stop();
	Sockets::Message CollectMessage();
	BlockingQueue<Sockets::Message>* GetQueue();
private:
	BlockingQueue<Sockets::Message> _receiveQueue;
	Sockets::SocketListener _listener;
};

template<typename CallableObject>
void Receiver::Start(CallableObject& callableObject)
{
	_listener.Start(callableObject);
}

#endif // !RECEIVER_H
