#pragma once

////////////////////////////////////////////////////////////////////////////
// Sender.h - A class that sends messages on a socket                     //
// ver 1.0																  //
////////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package contains a Sender class that sends messages
* on a socket by queueing them up in a BlockingQueue.
*
* This is largely based on Prof. Fawcett's example code.
*
* Required Files:
* ---------------
* Message.h, Socket.h, BlockingQueue.h, Endpoint.h
*/

#ifndef SENDER_H
#define SENDER_H

#include "..\BlockingQueue\BlockingQueue.h"
#include "Message.h"
#include "Endpoint.h"
#include "Socket.h"
#include <thread>

class Sender
{
public:
	Sender();
	virtual ~Sender();
	void Start();
	void Stop();
	bool Connect(Sockets::EndPoint);
	void DeliverMessage(Sockets::Message);	
	BlockingQueue<Sockets::Message>* GetQueue();
private:
	bool SendFile(Sockets::Message);
	BlockingQueue<Sockets::Message> _sendQueue;
	Sockets::SocketConnector _connector;
	std::thread _sendThread;
	Sockets::EndPoint _lastReceiver;
};

#endif // !SENDER_H