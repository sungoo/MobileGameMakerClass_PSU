#include "pch.h"
#include "Session.h"
#include "Serviece.h"
#include "SocketUtility.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"

Session::Session()
	:_recvBuffer(BUFF_SIZE)
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
		ProcessSend(numOfBytes);
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

void Session::Send(shared_ptr<SendBuffer> buffer)
{
	WRITE_LOCK;

	_sendQueue.push(buffer);
	
	if (_sendRegistered.exchange(true) == false)
	{
		//sendRegisterd가 원래 false였고, true로 잘 바뀌었으면 들어오는곳
		RegisterSend();
	}
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
	wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer.WritePos());
	wsaBuf.len = _recvBuffer.FreeSize();

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

void Session::RegisterSend()
{
	if (IsConnected() == false)
		return;

	_sendEvent.Init();
	_sendEvent.SetOwner(shared_from_this());

	//보낼 데이터들을 _sendEvent에 등록
	{
		WRITE_LOCK;

		int32 writeSize = 0;
		while (_sendQueue.empty()==false)
		{
			shared_ptr<SendBuffer> buffer = _sendQueue.front();

			writeSize += buffer->WriteSize();
			//길이가 너무 길다... 등등의 예외처리

			_sendQueue.pop();
			_sendEvent.sendBuffers.push_back(buffer);
		}
	}

	//WSABUF wsaBuf;
	//wsaBuf.buf = _sendBuffer;
	//wsaBuf.len = 1000; //TODO
	Vector<WSABUF> wsaBufs;
	wsaBufs.reserve(_sendEvent.sendBuffers.size());
	for (auto sendBuffer : _sendEvent.sendBuffers)
	{
		WSABUF wsaBuf;
		wsaBuf.buf = reinterpret_cast<char*>(sendBuffer->Buffer());
		wsaBuf.len = static_cast<LONG>(sendBuffer->WriteSize());
		wsaBufs.push_back(wsaBuf);
	}

	DWORD numOfBytes = 0;

	//WSASend... Scatter Gather 기법을 지원

	if (SOCKET_ERROR == ::WSASend(_socket, wsaBufs.data(), static_cast<DWORD>(wsaBufs.size()), OUT & numOfBytes, 0, &_sendEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			_sendEvent.SetOwner(nullptr);
			_sendEvent.sendBuffers.clear();
			_sendRegistered.store(false);
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

	if (_recvBuffer.OnWrite(numOfBytes) == false)
	{
		DisConnect(L"OnWrite Overflow");
		return;
	}

	int32 dataSize = _recvBuffer.DataSize();
	int processLen = OnRecv(_recvBuffer.ReadPos(), dataSize);

	if (processLen < 0 || dataSize < processLen || _recvBuffer.OnRead(processLen) == false)
	{
		DisConnect(L"OnRead Overflow");
		return;
	}

	_recvBuffer.Clean();

	//재수신 등록
	RegisterRecv();
}

void Session::ProcessSend(int32 numOfBytes)
{
	_sendEvent.SetOwner(nullptr);//session Refcount -1
	_sendEvent.sendBuffers.clear();

	if (numOfBytes == 0)
	{
		DisConnect(L"Send 0");
		return;
	}
	OnSend(numOfBytes);

	WRITE_LOCK;
	if (_sendQueue.empty())
		_sendRegistered.store(false);
	else
		RegisterSend();
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

PacketSession::PacketSession()
{
}

PacketSession::~PacketSession()
{
}

//내가 Packet 형태의 데이터를 받았다.
//[PacketHead][Data ...]
//[4 byte][....]
int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
{
	int32 processLen = 0;

	while (true)
	{
		int32 dataSize = len - processLen;

		//PacketHeader로 파싱조차 안 되는 데이터는 보지도 않겠다.
		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader header = *(reinterpret_cast<PacketHeader*>(&buffer[processLen]));

		//해더에 기록된 데이터가, 실제 데이터보다 크다 => 아직 데이터가 다 안왔다.
		if (dataSize < header.size)
			break;

		//패킷 조립 성공
		OnRecvPacket(&buffer[processLen], header.size);
		processLen += header.size;
	}

	return processLen;
}