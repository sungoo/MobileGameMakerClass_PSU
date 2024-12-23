#pragma once

class Session;
class IocpObject;

enum class EventType : uint8
{
	CONNECT,
	DISCONNECT,
	ACCEPT,
	RECV,
	SEND,
};

//OVERLAPPED는 운영체제가 만들어줌
class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);
	//운영체제 것을 상속받았기에, 가상함수 사용 불가
	void Init();
	EventType GetType() { return _eventType; }

	shared_ptr<IocpObject>  GetOwner()								{ return _owner; }
	void					SetOwner(shared_ptr<IocpObject> owner)  { _owner = owner; }
protected:
	EventType				_eventType;
	shared_ptr<IocpObject>  _owner = nullptr;
};

/// <summary>
/// Connect
/// </summary>

class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() :IocpEvent(EventType::CONNECT) {};
};

/// <summary>
/// Connect
/// </summary>

class DisConnectEvent : public IocpEvent
{
public:
	DisConnectEvent() :IocpEvent(EventType::DISCONNECT) {};
};

/// <summary>
/// Accept
/// </summary>

class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() :IocpEvent(EventType::ACCEPT){};

	void SetSession(shared_ptr<Session> session) { _session = session; }
	shared_ptr<Session> GetSession() { return _session; }

private:
	//Owner : Listener
	//this : Client
	shared_ptr<Session> _session = nullptr;
};

/// <summary>
/// Recv
/// </summary>

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() :IocpEvent(EventType::RECV){};

	//Owner : Client
};

/// <summary>
/// Send
/// </summary>

class SendEvent : public IocpEvent
{
public:
	SendEvent() :IocpEvent(EventType::SEND){};

	Vector<shared_ptr<class SendBuffer>> sendBuffers;
};
