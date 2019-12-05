#include "stdafx.h"
#include "..\Utilities\converter.h"
#include "Message.h"
#include "Endpoint.h"
#include <objbase.h>
#include <sstream>
#include <vector>

using namespace Sockets;

// Generate a random GUID as a string
std::string GetNewMessageID()
{
	GUID guid;
	CoCreateGuid(&guid);
	return Convert::GuidToString(guid);
}

// Set the message id
Message::Message()
{
	_messageId = GetNewMessageID();
}

// Set the source and destination
Message::Message(EndPoint source, EndPoint destination) : _source(source), _destination(destination)
{
	_messageId = GetNewMessageID();
}

// Deserialize a string onto a message object
// This is basically the reverse of the ToString() method
Message::Message(std::string serializedMessage)
{
	std::vector<std::string> list = Convert::StringToList(serializedMessage);
	for (std::string kvp : list)
	{
		size_t index = kvp.find_first_of(':');
		if (index == kvp.length())
			continue;
		std::string key = kvp.substr(0, index), value = kvp.substr(index + 1, kvp.length() - index);
		if (key == "MESSAGE-ID")
			_messageId = value;
		if (key == "SOURCE")
			SetSource(EndPoint(value));
		if (key == "DESTINATION")
			SetDestination(EndPoint(value));
		if (key == "TYPE")
		{
			if (value == "0")
				SetType(MessageType::SHUTDOWN);
			if (value == "1")
				SetType(MessageType::REQUEST);
			if (value == "2")
				SetType(MessageType::READY);
			if (value == "3")
				SetType(MessageType::FILE);
			if (value == "4")
				SetType(MessageType::EXECUTE);
			if (value == "5")
				SetType(MessageType::ROGER_THAT);
		}
		if (key == "CONTENT-LENGTH")
			SetContentLength(Convert::FromString<size_t>(value));
		if (_contentLength < 0)
			_contentLength = 0;
		if (key == "BODY")
			SetBody(value);
	}
}

// Message created with string source and destination
Message::Message(std::string source, std::string destination) : _source(EndPoint(source)), _destination(EndPoint(destination))
{
	_messageId = GetNewMessageID();
}

// Returns the message id
std::string Message::GetMessageId()
{
	return _messageId;
}

// Returns the source
EndPoint Message::GetSource()
{
	return _source;
}

// Returns the destination
EndPoint Message::GetDestination()
{
	return _destination;
}

// Returns the message type
MessageType Message::GetType()
{
	return _type;
}

// Returns the timestamp
Message::timestamp Message::GetTimestamp()
{
	return _datetime;
}

// Returns the body
std::string Message::GetBody()
{
	return _body;
}

// Returns the content length
size_t Message::GetContentLength()
{
	return _contentLength;
}

// Sets the source
void Message::SetSource(EndPoint source)
{
	_source = source;
}

// Sets the destination
void Message::SetDestination(EndPoint destination)
{
	_destination = destination;
}

// Sets the type
void Message::SetType(MessageType type)
{
	_type = type;
}

// Sets the timestamp
void Message::SetTimestamp(timestamp datetime)
{
	_datetime = datetime;
}

// Sets the body
void Message::SetBody(std::string body)
{
	_body = body;
}

// Sets the content length
void Message::SetContentLength(size_t contentLength)
{
	_contentLength = contentLength;
}

// Serializes as string
std::string Message::ToString()
{
	std::ostringstream serializedMessage;
	serializedMessage << "MESSAGE-ID:" << _messageId << std::endl;
	serializedMessage << "SOURCE:" << _source.AsString() << std::endl;
	serializedMessage << "DESTINATION:" << _destination.AsString() << std::endl;
	serializedMessage << "TYPE:" << _type << std::endl;
	serializedMessage << "CONTENT-LENGTH:" << _contentLength << std::endl;
	serializedMessage << "BODY:" << _body << std::endl;
	return serializedMessage.str();
}