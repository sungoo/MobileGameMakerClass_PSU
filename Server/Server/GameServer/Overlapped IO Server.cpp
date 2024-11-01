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

	WSAOVERLAPPED overlapped = {};//WSASend, WSARecv 했을 때, 성공 실패사유 확인
};

int main()
{
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

	// Overlapped Socket IO(비동기, 논블로킹 소켓 입출력 방식)
	// WSASend, WSARecv
	// (AcceptEx, ConnectEx)
	// 1. Overlapped 함수를 건다.
	// 2. Overlapped 함수가 성공했는지 확인
	// 3. -> 성공했으면 결과 얻어서 처리
	//    -> 실패했으면 사유 확인하고(Pending 상태면 그대로 다음 꺼 진행)

	// Overlapped Event 기반 IO 모델의 장점
	// 1. (비동기, 논블로킹)
	// 
	// 단점
	// 1. 성능
	//	  - session과 wsaEvent를 묶어줘야 한다.
	//		=> 1000명의 session(client)를 위해 1000개의 wsaEvent가 필요.
	// ...     최대 64개 만큼만 지원
	// 결론 : 서버에 적합한 모델이 아니다.
	// 
	//
	while (true)
	{
		SOCKADDR_IN clientAddr;
		int32 addrLen = sizeof(clientAddr);

		SOCKET clientSocket;

		//Accept 준비
		while (true)
		{
			clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
			if (clientSocket != INVALID_SOCKET)
				break;
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;

			//문제 있는 상황..
			return 0;
		}
		Session session = Session{ clientSocket };
		WSAEVENT wsaEvent = ::WSACreateEvent();//WSASend , WSARecv 완료 상태 체크
		session.overlapped.hEvent = wsaEvent;

		cout << "Client Connected!" << endl;

		while (true)
		{
			WSABUF wsaBuf;
			wsaBuf.buf = session.recvBuffer;
			wsaBuf.len = BuffSize;

			DWORD recvLen = 0;
			DWORD flags = 0;

			//비동기 WSARecv
			if (::WSARecv(clientSocket, &wsaBuf, 1, &recvLen,
				&flags, &session.overlapped, nullptr) == SOCKET_ERROR)
			{
				//WSARecv 실패
				if (::WSAGetLastError() == WSA_IO_PENDING)
				{
					//Pending : 보류하고 나중에 확인
					::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
					::WSAGetOverlappedResult(session.socket, &session.overlapped, &recvLen, FALSE, &flags);
				}
				else
				{
					//TODO : 진짜 문제있는 상황
					break;
				}
				cout << "Data Recv! Len : " << recvLen << endl;

				for (int i = 0; i < recvLen; i++)
				{
					if (session.recvBuffer[i] == '\0') break;
					cout << session.recvBuffer[i];
				}
				cout << endl;
			}

			char sendBuff[100] = "Hello Im Server!";
			//Send
			wsaBuf.buf = sendBuff;
			wsaBuf.len = sizeof(sendBuff);

			DWORD sendLen = 0;
			flags = 0;

			if (::WSASend(session.socket, &wsaBuf, 1, &sendLen,
				flags, &session.overlapped, nullptr) == SOCKET_ERROR)
			{
				if (::WSAGetLastError() == WSA_IO_PENDING)
				{
					::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
					::WSAGetOverlappedResult(session.socket, &session.overlapped, &sendLen, FALSE, &flags);
				}
				else
				{
					break;
				}
			}
			cout << "Send Data! Len = " << sizeof(sendBuff) << endl;

			::closesocket(session.socket);
			::WSACloseEvent(wsaEvent);
		}
	}

	::WSACleanup();
	return 0;
}