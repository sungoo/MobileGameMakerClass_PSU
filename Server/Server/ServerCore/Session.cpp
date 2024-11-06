#include "pch.h"
#include "Session.h"
#include "IocpEvent.h"

Session::Session()
{
	_socket = SocketUtility::CreateSocket();
}

Session::~Session()
{
	SocketUtility::Close(_socket);
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Session::DisPatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	EventType eventType = iocpEvent->GetType();
	
	switch (eventType)
	{
	case EventType::CONNECT:
		break;
	case EventType::ACCEPT:
		break;
	case EventType::RECV:
		break;
	case EventType::SEND:
		break;
	default:
		break;
	}
}
