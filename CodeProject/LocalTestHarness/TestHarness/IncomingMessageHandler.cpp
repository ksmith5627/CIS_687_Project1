
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 3
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/
#include "stdafx.h"
#include "IncomingMessageHandler.h"
#include "..\Utilities\converter.h"
#include <objbase.h>
#include <fstream>

using namespace Sockets;

const int BLOCK_SIZE = 1048576;

// Set the test request queue
void IncomingMessageHandler::SetTestRequestQueue(BlockingQueue<Message>* queuePointer)
{
	_testRequestQPtr = queuePointer;
}

// Set the ready worker queue
void IncomingMessageHandler::SetReadyWorkerQueue(BlockingQueue<Sockets::Message>* queuePointer)
{
	_readyWorkerQPtr = queuePointer;
}

// Set the sender queue
void IncomingMessageHandler::SetSendMessageQueue(BlockingQueue<Sockets::Message>* queuePointer)
{
	_sendMessageQPtr = queuePointer;
}

// Read a message from a socket as a string
std::string IncomingMessageHandler::ReadMessage(Socket& socket)
{
	std::string temp, message;
	char buffer[BLOCK_SIZE];
	size_t blockSize;
	if (socket.IsValidState())
	{
		blockSize = socket.ReceiveStream(BLOCK_SIZE, buffer);
		if (blockSize > 0)
		{
			temp = buffer;
			message += temp.substr(0, blockSize);
		}
	}
	return message;
}

// Receive a file if send on the socket
bool IncomingMessageHandler::ReceiveFile(Message message)
{
	// Use the message id to create a directory
	// Ensuring that each request's files are stored
	// in unique locations to not override files from
	// other requests.
	CreateDirectory(message.GetMessageId().c_str(), NULL);

	// The filename is the message body
	std::string fileName = message.GetBody();
	std::string downloadLocation = message.GetMessageId() + "/" + fileName;
	std::ofstream outstream(downloadLocation, std::ios::binary);
	if (!outstream.good())
	{
		return false;
	}

	// Read BLOCK_SIZE bytes at a time, until we have no more bytes to read.
	char buffer[BLOCK_SIZE];
	ZeroMemory(buffer, BLOCK_SIZE);
	size_t filesize = message.GetContentLength();
	if (filesize == 0)
		return false;

	while (filesize > 0)
	{
		size_t bytesRead = _socketPointer->ReceiveStream(filesize > BLOCK_SIZE ? BLOCK_SIZE: filesize, buffer);
		if (bytesRead == 0)
			return false;
		outstream.write(buffer, bytesRead);
		filesize -= bytesRead;
	}
	outstream.flush();
	outstream.close();
	return true;
}

// Overloading the () operator to make this a functor
void IncomingMessageHandler::operator()(Socket socket)
{
	_socketPointer = &socket;
	while (socket.IsValidState())
	{
		// Read a message from the socket
		std::string messageString = ReadMessage(socket);
		if (messageString.length() == 0)
			break;

		// Deserialize it to a message object
		Message message(messageString);
		// If it's a file, download it
		if (message.GetType() == MessageType::FILE)
		{
			std::cout << "Received a file (" << message.GetBody() << ") with MessageID (" << message.GetMessageId()  <<") from " << message.GetSource().AsString() << std::endl;
			ReceiveFile(message);
			continue;
		}

		// If it's a worker signaling they're ready,
		// Queue them up in the ReadyWorkerQ
		if (message.GetType() == MessageType::READY)
		{
			std::cout << "Worker process on " << message.GetSource().AsString() << " is ready" << std::endl;
			_readyWorkerQPtr->EnQueue(message);
			continue;
		}

		// If it's a test request, queue it up in the
		// TestRequestQ, and send an acknowledgement back
		// to the client
		if (message.GetType() == MessageType::REQUEST)
		{
			if (message.GetSource().GetUriHost() == "")
				break;
			std::cout << "Received a test request (" << message.GetMessageId() << ")from " << message.GetSource().AsString() << std::endl;
			_testRequestQPtr->EnQueue(message);
			Message ack;
			ack.SetDestination(message.GetSource());
			ack.SetType(MessageType::ROGER_THAT);
			std::cout << "Sending acknowledgement of test request to " << message.GetSource().AsString() << std::endl;
			_sendMessageQPtr->EnQueue(ack);
			continue;
		}
		
		// If it's a SHUTDOWN message from self, stop
		if (message.GetType() == MessageType::SHUTDOWN)
			break;
	}
}