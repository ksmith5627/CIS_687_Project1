#include "stdafx.h"
#include "Sender.h"
#include <fstream>

using namespace Sockets;

const int BLOCK_SIZE = 1048576;

// Default constructor
Sender::Sender(){}

Sender::~Sender()
{
	if (_sendThread.joinable())
		_sendThread.join();
}

// Create a thread that dequeues from the blocking queue
// and sends a message to an endpoint given by the message
// destination
void Sender::Start()
{
	auto threadProc = [&]()
	{
		while (true)
		{			
			Message message = _sendQueue.DeQueue();
			if (message.GetType() == MessageType::SHUTDOWN)
			{
				_connector.ShutDown();
				break;
			}
			if (message.GetDestination().AsString() != _lastReceiver.AsString())
			{
				_connector.ShutDown();
				if (!Connect(message.GetDestination()))
				{
					std::cout << "Couldn't connect to " << message.GetDestination().AsString() << std::endl;
					continue;
				}
			}
			std::string serializedMessage = message.ToString();			
			_connector.SendBuffer(serializedMessage.length(), (char*)serializedMessage.c_str());
			Sleep(2000);
			if (message.GetType() == MessageType::FILE)
			{
				SendFile(message);
			}

		}
	};
	std::thread thread(threadProc);
	_sendThread = std::move(thread);
}

// Stop by sending a shutdown message to self
void Sender::Stop()
{
	Message message;
	message.SetType(MessageType::SHUTDOWN);
	DeliverMessage(message);
}

// Connect to an endpoint (Required before sending message)
bool Sender::Connect(EndPoint endPoint)
{
	_lastReceiver = endPoint;
	return _connector.Connect(endPoint.GetUriHost(), endPoint.GetPort());
}

// Send a message to an endpoint
void Sender::DeliverMessage(Message message)
{
	_sendQueue.EnQueue(message);
}
// Send a file where the filename is in the message body
bool Sender::SendFile(Message message)
{
	if (message.GetType() != MessageType::FILE)
		return false;
	std::ifstream file(message.GetBody(), std::ios::binary);
	if (!file.good())
		return false;

	char buffer[BLOCK_SIZE];
	while(true)
	{
		file.read(buffer, BLOCK_SIZE);
		size_t blockSize = (size_t)file.gcount();		
		if (blockSize == 0)
			break;
		_connector.SendBuffer(blockSize, buffer);
	}
	file.close();
	return true;
}

// Return a pointer to the blocking queue
BlockingQueue<Sockets::Message>* Sender::GetQueue()
{
	return &_sendQueue;
}