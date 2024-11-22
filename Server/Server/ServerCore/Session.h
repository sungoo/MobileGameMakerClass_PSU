#pragma once
#include "IocpCore.h"
#include "IocpEvent.h"
#include "RecvBuffer.h"

class Serviece;

class Session : public IocpObject
{
	friend class Listener;

	enum
	{
		BUFF_SIZE = 0x10000
	};

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
	void Send(shared_ptr<SendBuffer> buffer);
	void DisConnect(const WCHAR* cause);

	// - 내부에서만 쓸 함수
private:
	bool RegisterConnect();//손님이 식탁에 앉기
	bool RegisterDisConnect();
	void RegisterRecv();//손님이 주는 메시지 -> 커널의 RecvBuffer -> 유저영역 Session::RecvBuffer에 복사
	void RegisterSend();//내가 손님에게 줄 메시지

	void ProcessConnect();
	void ProcessDisConnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(int32 numOfBytes);

	void HandleError(int32 errorCode);

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
	RecvBuffer _recvBuffer;
	Queue<shared_ptr<SendBuffer>> _sendQueue;
	Atomic<bool> _sendRegistered = false;

	//송신 관련

	SendEvent		_sendEvent;
	RecvEvent		_recvEvent;
	ConnectEvent	_connectEvent;
	DisConnectEvent _disconnectEvent;
};

// PacketSession
// Packet이 왜 필요한가
// SendBuff로 데이터를 전달할 때, TCP 환경에서는 데이터 한 묶음이 다 전달된다는 보장이 없다.
// 
// Packet으로 확인해야할 것
// 1. 어떤 종류의 데이터인지
// 2. 이 데이터의 총 크기는 어떻데 되는지.
//
struct PacketHeader
{
	uint16 size;
	uint16 id;
};

class PacketSession : public Session
{
public:
	PacketSession();
	~PacketSession();

	shared_ptr<PacketSession> GetPacketSession() { return static_pointer_cast<PacketSession>(shared_from_this()); }

protected:
	virtual int32 OnRecv(BYTE* buffer, int32 len) sealed;
	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) abstract;
};