#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

const int32 BuffSize = 1000;

struct Session
{
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[BuffSize] = {};
	char sendBuffer[100] = "Hello Im Server!!";
	int32 recvBytes = 0;
	int32 sendBytes = 0;
};

enum IO_TYPE
{
	READ,
	WRITE,
	ACCEPT,
	CONNET
	//Packet Header...추가가능
};

struct OverlappedEx
{
	WSAOVERLAPPED overlapped = {};
	int32 type = 0; //read, write, accept, connet...
};

//스레드 5개에 부여될 일감 => 결과 보기
void WorkerThreadMain(HANDLE iocpHandle)
{
	while (true)
	{
		//GetQueuedCompletionStatus => 결과 처리
		DWORD bytesTranferred = 0;//전송된 크기
		Session* session = nullptr;
		OverlappedEx* overlappedEx = nullptr;

		//ret == true => recv 완료 상태
		BOOL ret = ::GetQueuedCompletionStatus(iocpHandle, &bytesTranferred, /*Key*/(ULONG_PTR*)&session,
			(LPOVERLAPPED*)overlappedEx, INFINITE);

		if (ret == false || bytesTranferred == 0)
		{
			//연결 끊김
			continue;
		}

		//session과 overlapped 세팅완료

		//처리
		switch (overlappedEx->type)
		{
		case IO_TYPE::READ:
		{
			cout << session->recvBuffer << endl;

			WSABUF wsaBuf;
			wsaBuf.buf = session->recvBuffer;
			wsaBuf.len = BuffSize;

			DWORD recvLen = 0;
			DWORD flags = 0;
			//다시 예약 걸어주기
			::WSARecv(session->socket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL);

			break;
		}

		//TODO

		default:
			break;
		}
	}
}

int main()
{
	CoreGlobal::Create();

	SocketUtility::Init();

	SOCKET listenSocket = SocketUtility::CreateSocket();
	ASSERT_CRASH(listenSocket != INVALID_SOCKET);

	/*u_long on = 1;
	ASSERT_CRASH(::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET);*/

	//TODO : DELETED
	SocketUtility::BindAnyAddress(listenSocket, 7777);

	SocketUtility::Listen(listenSocket);

	SOCKET clientSocket = ::accept(listenSocket, nullptr, nullptr);

	cout << "Client Connected" << endl;

	while (true)
	{
		
	}

	TM_M->Join();

	SocketUtility::Clear();

	CoreGlobal::Delete();

	return 0;
}