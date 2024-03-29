
/*
Team Members:		Julia Thee, Derek Janzen, Jess Lembke and Kenneth Smith
Course:				CIS 687 -  Object Oriented Design
Assignment:			CIS 687 Homework 4
Instructor:			Professor Scott Roueche

					College of Engineering & Computer Science
					Syracuse University
*/

//////////////////////////////////////////////////////////////////////////
// Translator.cpp - Translates messages to/from managed and native types//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\CommunicationFactory\CommunicationFactory.h"
#include "..\Socket\ICommunication.h"
#include "Translator.h"
#include "..\Utilities\File.h"
#include "..\Utilities\Converter.h"
#include "Utilities.h"


using namespace Translator;
using namespace System;
using namespace System::Text;
using namespace System::IO;

// Convert managed enpoint to native endpoint
Sockets::EndPoint EndPoint::AsNativeEndPoint()
{
	Sockets::EndPoint nativeEndpoint(*StringUtilities::Convert::ManagedStringToNative(AsString()));
	return nativeEndpoint;
}

// Convert native endpoint to managed endpoint
EndPoint^ EndPoint::FromNativeEndPoint(Sockets::EndPoint& nativeEndpoint)
{
	EndPoint^ endpoint = gcnew EndPoint();
	endpoint->Address = StringUtilities::Convert::NativeStringToManaged(nativeEndpoint.GetUriHost());
	endpoint->Port = nativeEndpoint.GetPort();
	return endpoint;
}

// Implement the AsString() function for the managed endpoint
String^ EndPoint::AsString()
{
	StringBuilder ^stringBuilder = gcnew StringBuilder();
	stringBuilder->Append(Address);
	stringBuilder->Append(":");
	stringBuilder->Append(Port);
	return stringBuilder->ToString();
}

// Convert managed message to native message
Sockets::Message* Message::AsNativeMessage()
{
	Sockets::Message *nativeMessage = new Sockets::Message();
	nativeMessage->SetSource(Source->AsNativeEndPoint());
	nativeMessage->SetDestination(Destination->AsNativeEndPoint());
	nativeMessage->SetType(static_cast<Sockets::MessageType>(static_cast<int>(Type)));
	nativeMessage->SetFilename(*StringUtilities::Convert::ManagedStringToNative(Filename));
	nativeMessage->SetContentLength(ContentLength);
	nativeMessage->SetBody(*StringUtilities::Convert::ManagedStringToNative(Body));
	return nativeMessage;
}

// Convert native message to managed message
Message^ Message::FromNativeMessage(Sockets::Message& nativeMessage)
{
	Message^ message = gcnew Message();
	message->MessageId = StringUtilities::Convert::NativeStringToManaged(nativeMessage.GetMessageId());
	message->Source = EndPoint::FromNativeEndPoint(nativeMessage.GetSource());
	message->Destination = EndPoint::FromNativeEndPoint(nativeMessage.GetDestination());
	message->ContentLength = nativeMessage.GetContentLength();
	message->Body = StringUtilities::Convert::NativeStringToManaged(nativeMessage.GetBody());
	message->Filename = StringUtilities::Convert::NativeStringToManaged(nativeMessage.GetFilename());
	message->Type = (MessageType)static_cast<int>(nativeMessage.GetType());
	return message;
}

// The ICommunication object initialization
Communication::Communication(size_t port, int context)
{
	Sockets::CommunicationFactory *factory = new Sockets::CommunicationFactory();
	_communication = factory->CreateInstance(port);
	_communication->ProcessContext = (Sockets::CONTEXT)context;
	delete factory;
}

// Collect a message from the communication channel
// Convert it to a managed message before returning
Message^ Communication::CollectMessage()
{
	return Message::FromNativeMessage(_communication->CollectMessage());
}

// Convert a managed message to native
// and deliver it via the communication channel
void Communication::DeliverMessage(Message^ message)
{
	Sockets::Message* nativeMessage = message->AsNativeMessage();
	_communication->DeliverMessage(*nativeMessage);
}

// Call the start function on the communication channel
// so it can send and receive messages
void Communication::StartListening()
{
	_communication->Start();
}