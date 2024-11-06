#pragma once
#include "IocpCore.h"

class Session : public IocpObject
{
public:
	Session();
	virtual ~Session();
	
public:
	void SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress GetAddress() { return _netAddress; }
	SOCKET GetSocket() { return _socket; }

	virtual HANDLE GetHandle() override;
	virtual void DisPatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

	char _recvBuffer[1000] = {};
	char _sendBuffer[1000] = {};

private:
	SOCKET _socket = INVALID_SOCKET;
	NetAddress _netAddress = {};
};

