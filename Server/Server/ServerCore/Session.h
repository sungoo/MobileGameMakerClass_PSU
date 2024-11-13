#pragma once
#include "IocpCore.h"
#include "IocpEvent.h"

class Serviece;

class Session : public IocpObject
{
	friend class Listener;

public:
	Session();
	virtual ~Session();
	
public:
	//정보 관련
	shared_ptr<Serviece> GetService() { return _service.lock(); }
	void SetService(shared_ptr<Serviece> service);

	void SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress GetAddress() { return _netAddress; }
	SOCKET GetSocket() { return _socket; }

	virtual HANDLE GetHandle() override;
	virtual void DisPatch(class IocpEvent* iocpEvent, int32 numOfBytes) override;
	bool IsConnected() { return _connected; }
	shared_ptr<Session> GetSessionShared() {return static_pointer_cast<Session>(shared_from_this());}
	
	//전송 관련
	// - 외부(Client, Server)에서 쓸 함수
	bool Connect();
	void Send(BYTE* buffer, int32 len);
	void DisConnect(const WCHAR* cause);

	// - 내부에서만 쓸 함수
private:
	bool RegisterConnect();//손님이 식탁에 앉기
	bool RegisterDisConnect();
	void RegisterRecv();//손님이 주는 메시지 -> 커널의 RecvBuffer -> 유저영역 Session::RecvBuffer에 복사
	void RegisterSend(SendEvent* sendEvent);//내가 손님에게 줄 메시지

	void ProcessConnect();
	void ProcessDisConnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(SendEvent* event, int32 numOfBytes);

	void HandleError(int32 errorCode);

protected:
	char _recvBuffer[1000] = {};
	char _sendBuffer[1000] = {};

protected:
	//ServerSession, ClientSession에서 필요할 경우 오버라이딩
	virtual void OnConnected(){}
	virtual void OnDisConnected(){}
	virtual int32 OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void OnSend(int32 len){}
	virtual void Disconnected(){}

private:
	weak_ptr<Serviece> _service;
	SOCKET _socket = INVALID_SOCKET;
	NetAddress _netAddress = {};

	Atomic<bool> _connected = false;

private:
	USE_LOCK;
	//수신 관련

	//송신 관련

	RecvEvent _recvEvent;
	ConnectEvent _connectEvent;
	DisConnectEvent _disconnectEvent;
};

