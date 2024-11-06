#pragma once

class Session;

enum class EventType : uint8
{
	CONNECT,
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

protected:
	EventType _eventType;

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
/// Accept
/// </summary>

class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() :IocpEvent(EventType::ACCEPT){};

	void SetSession(Session* session) { _session = session; }
	Session* GetSession() { return _session; }

private:
	Session* _session;
};

/// <summary>
/// Recv
/// </summary>

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() :IocpEvent(EventType::RECV){};
};

/// <summary>
/// Send
/// </summary>

class SendEvent : public IocpEvent
{
public:
	SendEvent() :IocpEvent(EventType::SEND){};
};
