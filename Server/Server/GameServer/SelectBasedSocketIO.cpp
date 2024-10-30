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

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	//SELECT 기반 소켓 프로그래밍
	//소켓 함수 호출이 성공할 시점을 미리 알 수 있다.
	// ...문제
	// recvBuffer에 데이터가 없는데, recv에서 읽으려 한다. -> x
	// sendBuffer(커널)에 데이터가 꽉 찼는데, send함수(유저레벨 send -> 커널레벨 send로 복사)호출 -> x
	//
	// socket set
	// 1) 읽기, 쓰기, 예외 ... 관찰 대상 등록
	// 2) select(readSet, writeSet, exceptSet); => 관찰
	// 3) 적어도 하나의 소켓이 준비되면 리턴
	// 4) 남은 소켓 체크해서 진행
	//
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

	//Select기반 Socket IO (소켓 입출력)
	vector<Session> sessions;
	sessions.reserve(100);

	//소켓set
	fd_set reads;
	fd_set writes;


	while (true)
	{
		//소켓 셋 초기화
		FD_ZERO(&reads);
		FD_ZERO(&writes);

		//ListenSocket 등록
		FD_SET(listenSocket, &reads);

		//ClientSocket 등록
		for (auto& session : sessions)
		{
			if (session.recvBytes <= session.sendBytes)
				FD_SET(session.socket, &reads);
			else
				FD_SET(session.socket, &writes);
		}

		int32 retVal = ::select(0, &reads, &writes, nullptr, nullptr);//동기함수
		if (retVal == SOCKET_ERROR)
			break;

		//Check Listener Socket
		if (FD_ISSET(listenSocket, &reads))
		{
			SOCKADDR_IN clientAddr;
			int32 addrLen = sizeof(clientAddr);
			SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
			if (clientSocket != INVALID_SOCKET)
			{
				//클라이언트 접속
				cout << "Client Connected" << endl;
				sessions.push_back(Session{ clientSocket });
			}
		}

		//나머지 소켓 체크
		for (Session& session : sessions)
		{
			//Read
			if (FD_ISSET(session.socket, &reads))
			{
				int32 recvLen = ::recv(session.socket, session.recvBuffer, BuffSize, 0);
				if (recvLen <= 0)
				{
					//TODO : Session Disconnect
					continue;
				}
				session.recvBytes = recvLen;
				cout << "RecvSize : " << session.recvBytes << endl;
			}

			//현재 상황
			// - client가 10개짜리 문자열을 보냈고, 10개를 받은 상황
			// - 처음 recv 받고, 첫 send하기 시작
			// recvBytes = 10
			// sendBytes = 0

			//Write
			if (FD_ISSET(session.socket, &writes))
			{
				//블로킹 모드 -> 모든 데이터를 다 보낼 때 까지 대기
				//논블로킹 모드 -> 상대방의 recvBuff에 따라, 일부만 보낼 수 있음
				int32 sendLen = ::send(session.socket, session.recvBuffer, sizeof(session.recvBytes - session.sendBytes), 0);
				//sendLen : 보냈을 때 그 길이
				if (sendLen == SOCKET_ERROR)
				{
					//TODO : Disconnect
					continue;
				}

				session.sendBytes += sendLen;
				if (session.recvBytes == session.sendBytes)
				{
					session.sendBytes = 0;
					session.recvBytes = 0;
				}

				cout << "SendSize : " << session.sendBytes << endl;
			}
		}
	}

	::WSACleanup();
	return 0;
}