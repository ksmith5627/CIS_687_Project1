#include "stdafx.h"
#include "Communication.h"

using namespace Sockets;

// Constructor to set port to listen on
Communication::Communication(size_t port) : _receiver(port) {}

// Stop the sender and the receiver
void Communication::Stop()
{
	_receiver.Stop();
	_sender.Stop();
}

// Return a pointer to the receiver's blocking queue
BlockingQueue<Message>* Communication::GetReceiverQueue()
{
	return _receiver.GetQueue();
}

// Return a pointer to the sender's blocking queue
BlockingQueue<Message>* Communication::GetSenderQueue()
{
	return _sender.GetQueue(); 
}

// Queue up a message in the sender's blocking queue
void Communication::DeliverMessage(Message message)
{
	_sender.DeliverMessage(message);
}

// DeQueue a message from the receiver's blocking queue
Message Communication::CollectMessage()
{
	return _receiver.CollectMessage();
}
