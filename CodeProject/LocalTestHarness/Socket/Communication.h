#pragma once

////////////////////////////////////////////////////////////////////////////
// Communication.h - A class that encapsulates both a Sender and Receiver //
// ver 1.0																  //
////////////////////////////////////////////////////////////////////////////

/*
* Package Operations:
* -------------------
* This package contains a Communication class that encapsulates 
* both a sender and a receiver. The communication happens through
* messages defined by the Message class.
*
* This is largely based on Prof. Fawcett's example code.
*
* Required Files:
* ---------------
* Message.h, Sender.h, Receiver.h
*/


#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "Message.h"
#include "Receiver.h"
#include "Sender.h"

namespace Sockets {
	class Communication
	{
	public:
		Communication(size_t);
		template <typename CallableObject>
		void Start(CallableObject&);
		void Stop();
		BlockingQueue<Message>* GetReceiverQueue();
		BlockingQueue<Message>* GetSenderQueue();
		void DeliverMessage(Message);
		Message CollectMessage();
	private:
		Sender _sender;
		Receiver _receiver;
	};

	template <typename CallableObject>
	void Communication::Start(CallableObject& callableObject)
	{
		_receiver.Start(callableObject);
		_sender.Start();		
	}
}
#endif // !COMMUNICATION_H

