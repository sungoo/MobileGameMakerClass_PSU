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

	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
		return 0;

	u_long on = 1;
	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET)//논블로킹 소켓 만드는 함수
		return 0;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	if (::bind(listenSocket, (sockaddr*)(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)//listen 최대크기를 넘어도 에러
		return 0;

	cout << "Accept" << endl;

	//Overlapped 모델 (Complition Routine 콜백기반) => 비동기 + 논블럭
	// - 장점 : 비동기 + 논블럭
	// - 단점 : 스레드마다 APC큐가 있다.
	//			스레드를 Alertable Wait 부담
	//			이벤트 방식 소켓 : 이벤트 = 1 : 1 대응
	// 
	// IOCP (Input Output Completion Port) 모델
	// - APC큐 => Completion Port로 바뀜(*스레드마다 한개씩이 아니라, 중앙관리)
	// - Aleratable Wait => CP 결과 처리를 GetQueuedCompletionStatus
	// ==> 멀티스레드 환경에 매우 적합
	
	//CreateIoCompletionPort => CP 생성, / CP에 소켓 연동
	//GetQueuedCompletionStatus => 결과 처리

	vector<Session*> sessionManager;

	//CP생성
	HANDLE iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	//멀티스레드 환경 만들기
	for (int32 i = 0; i < 5; i++)
	{
		TM_M->Launch([=]() {WorkerThreadMain(iocpHandle); });
	}

	//Main Thread Accept
	while (true)
	{
		SOCKADDR_IN clientAddr;
		int32 addrLen = sizeof(clientAddr);

		//TODO : accept -> acceptEx
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET) continue;

		Session* session = xnew<Session>();
		session->socket = clientSocket;
		sessionManager.push_back(session);

		cout << "Client Connected!" << endl;

		//소켓을 CP에 등록 : cp에게 소켓을 관찰해달라 요청
		::CreateIoCompletionPort((HANDLE)clientSocket, iocpHandle, /*Key*/(ULONG_PTR)session, 0);

		//Recv 예약
		WSABUF wsaBuf;
		wsaBuf.buf = session->recvBuffer;
		wsaBuf.len = BuffSize;

		OverlappedEx* overlappedEx = xnew<OverlappedEx>();
		overlappedEx->type = IO_TYPE::READ;

		DWORD recvLen = 0;
		DWORD flags = 0;
		::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL);//Overlapped와 동일한 WSARecv
	}

	TM_M->Join();

	::WSACleanup();

	CoreGlobal::Delete();

	return 0;
}