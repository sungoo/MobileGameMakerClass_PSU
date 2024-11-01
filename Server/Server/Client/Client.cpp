#include "pch.h"

// Socket 만들기
// - ipv6
// - port
// - protocol
//
#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);//socket의 번호를 발급
	if (clientSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErrorCode : " << errCode << endl;
		return 0;
	}

	u_long on = 1;
	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)//논블로킹 소켓 만드는 함수
		return 0;

	SOCKADDR_IN serverAddr;//IPv4
	::memset(&serverAddr, 0, sizeof(serverAddr));//serverAddr 0으로 다 밀어버리기
	serverAddr.sin_family = AF_INET;//IPv4
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);//127.0.01 => Loop back : 자기 PC의 주소
	serverAddr.sin_port = ::htons(7777); //1~1000 사이 포트는 건들면 안됨
	
	this_thread::sleep_for(1s);

	//Connect
	while (true)
	{
		if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		{
			// 블록상태여야 했음(연결이 아직 되지 않음)
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			// 이미 연결상태임
			if (::WSAGetLastError() == WSAEISCONN)
				break;
			// Error
			break;
		}
	}

	cout << "connected to server!!" << endl;

	// - Session
	char sendBuff[100] = "Hello world!!";
	//Overlapped
	WSAEVENT wsaEvent = WSACreateEvent();
	WSAOVERLAPPED overlapped = {};
	overlapped.hEvent = wsaEvent;

	//Send
	while (true)
	{
		WSABUF wsaBuf;
		wsaBuf.buf = sendBuff;
		wsaBuf.len = sizeof(sendBuff);

		DWORD sendLen = 0;
		DWORD flags = 0;

		if (::WSASend(clientSocket, &wsaBuf, 1, &sendLen, 
			flags, &overlapped, nullptr) == SOCKET_ERROR)
		{
			//WSASend 실패
			if (::WSAGetLastError() == WSA_IO_PENDING)
			{
				//Pending : 보류하고 나중에 확인
				::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
				::WSAGetOverlappedResult(clientSocket, &overlapped, &sendLen, FALSE, &flags);
			}
			else
			{
				//TODO : 진짜 문제있는 상황
				break;
			}
		}
		cout << "Send Data! Len = " << sizeof(sendBuff) << endl;


		//Recv
		char recvBuff[1000];
		wsaBuf.buf = recvBuff;
		wsaBuf.len = sizeof(recvBuff);

		DWORD recvLen = 0;
		flags = 0;

		if (::WSARecv(clientSocket, &wsaBuf, 1, &recvLen,
			&flags, &overlapped, nullptr) == SOCKET_ERROR)
		{
			if (::WSAGetLastError() == WSA_IO_PENDING)
			{
				::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
				::WSAGetOverlappedResult(clientSocket, &overlapped, &recvLen, FALSE, &flags);
			}
			else
			{
				//여기서 걸림..
				break;
			}
			cout << "Data Recv! Len : " << recvLen << endl;

			for (int i = 0; i < recvLen; i++)
			{
				if (recvBuff[i] == 0) break;
				cout << recvBuff[i];
			}
			cout << endl;
		}

		this_thread::sleep_for(1s);
	}

	
	WSACloseEvent(wsaEvent);
	::closesocket(clientSocket);
	::WSACleanup();
}
