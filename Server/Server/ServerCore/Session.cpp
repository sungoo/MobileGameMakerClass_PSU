#include "pch.h"
#include "Session.h"
#include "Serviece.h"
#include "SocketUtility.h"

Session::Session()
{
	_socket = SocketUtility::CreateSocket();
}

Session::~Session()
{
	SocketUtility::Close(_socket);
}

void Session::SetService(shared_ptr<Serviece> service)
{
	_service = service;

	u_long on = 1;
	if (::ioctlsocket(_socket, FIONBIO, &on) == INVALID_SOCKET)
		return;

	_netAddress = service->GetNetAddress();

	//SocketUtility::Bind(_socket, _service.lock()->GetNetAddress());
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
	{
		ProcessConnect();
		break;
	}
	case EventType::RECV:
	{
		ProcessRecv(numOfBytes);
		break;
	}
	case EventType::SEND:
	{
		ProcessSend(static_cast<SendEvent*>(iocpEvent), numOfBytes);
		break;
	}
	case EventType::DISCONNECT:
	{
		ProcessDisConnect();
		break;
	}
	default:
		break;
	}
}

bool Session::Connect()
{
	return RegisterConnect();
}

void Session::Send(BYTE* buffer, int32 len)
{
	//TODO : Scatter Gathering

	SendEvent* sendEvent = xnew<SendEvent>();
	sendEvent->SetOwner(GetSessionShared());

	::memcpy(_sendBuffer, buffer, len);
	
	WRITE_LOCK;
	RegisterSend(sendEvent);
}

void Session::DisConnect(const WCHAR* cause)
{
	if (_connected.exchange(false) == false)//connected가 애초에 false
		return;

	wcout << "Disconnected : " << cause << endl;

	OnDisConnected();

	GetService()->ReleaseSession(GetSessionShared()); //refCount - 1

	RegisterDisConnect();
}

bool Session::RegisterConnect()
{
	if (IsConnected())
		return false;

	//분산서버
	if (GetService()->GetServiceType() != ServiceType::CLIENT)
		return false;

	if (SocketUtility::SetReuseAddress(_socket, true) == false)
		return false;

	if (SocketUtility::BindAnyAddress(_socket, 0) == false)
		return false;

	_connectEvent.Init();
	_connectEvent.SetOwner(shared_from_this());

	DWORD numOfBytes = 0;
	SOCKADDR_IN sockAddr = GetService()->GetNetAddress().GetSockAddr();

	if (false == SocketUtility::ConnectEx(_socket, reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(&sockAddr), nullptr, 0, &numOfBytes, &_connectEvent))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			_connectEvent.SetOwner(nullptr);
			return false;
		}
	}
	return true;
}

bool Session::RegisterDisConnect()
{
	_disconnectEvent.Init();
	_disconnectEvent.SetOwner(shared_from_this());

	if (false == SocketUtility::DisConnectEx(_socket, &_disconnectEvent, TF_REUSE_SOCKET, 0))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			_disconnectEvent.SetOwner(nullptr);
			return false;
		}
	}
	return true;
}

void Session::RegisterRecv()
{
	if (IsConnected() == false) return;
	
	_recvEvent.Init();
	_recvEvent.SetOwner(shared_from_this());//event의 주인이 IocpObject.. Session의 refCount++

	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer);
	wsaBuf.len = len32(_recvBuffer));

	DWORD numOfBytes = 0;
	DWORD flags = 0;

	if (SOCKET_ERROR == ::WSARecv(_socket, &wsaBuf, 1, OUT & numOfBytes, &flags, &_recvEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			
			_recvEvent.SetOwner(nullptr);//refCount - 1
		}
	}
}

void Session::RegisterSend(SendEvent* sendEvent)
{
	if (IsConnected() == false)
		return;

	WSABUF wsaBuf;
	wsaBuf.buf = _sendBuffer;
	wsaBuf.len = 1000; //TODO

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == ::WSASend(_socket, &wsaBuf, 1, OUT & numOfBytes, 0, sendEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			sendEvent->SetOwner(nullptr);
			xdelete(sendEvent);
		}
	}
}

void Session::ProcessConnect()
{
	_connectEvent.SetOwner(nullptr);//SessionRef--
	_connected.store(true);

	GetService()->AddSession(GetSessionShared());

	OnConnected();

	//연결 됐으니까 수신하겠다
	RegisterRecv();
}

void Session::ProcessDisConnect()
{
	_disconnectEvent.SetOwner(nullptr); //Session Ref --
}

//스레드 단 하나만 도착
void Session::ProcessRecv(int32 numOfBytes)
{
	_recvEvent.SetOwner(nullptr);//Session의 RefCount - 1

	if (numOfBytes == 0)
	{
		DisConnect(L"Recv : 0");
		return;
	}

	OnRecv(reinterpret_cast<BYTE*>(_recvBuffer), numOfBytes);

	//재수신 등록
	RegisterRecv();
}

void Session::ProcessSend(SendEvent* event, int32 numOfBytes)
{
	event->SetOwner(nullptr);//session Refcount -1
	xdelete(event);

	if (numOfBytes == 0)
	{
		DisConnect(L"Send 0");
		return;
	}
	OnSend(numOfBytes);
}

void Session::HandleError(int32 errorCode)
{
	switch (errorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
	{
		DisConnect(L"Handler Error");
		break;
	}
	default:
		cout << "Handle Error : " << errorCode << endl;
		break;
	}
}
