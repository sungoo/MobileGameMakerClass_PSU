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
	//윈속 초기화(ws2_32 라이브러리 초기화)
	//관련 정보가 wsaData에 채워짐
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	//1. Client Socket 만들기 => 서버에 연결 시킬 socket 만들기
	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);//socket의 번호를 발급
	if (clientSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErrorCode : " << errCode << endl;
		return 0;
	}

	//본인 = "127.0.0.1"
	//강사 = "192.168.0.9"

	//2. Server에 어디에 연결할지(Ip 주소 + 포트번호)
	SOCKADDR_IN serverAddr;//IPv4
	::memset(&serverAddr, 0, sizeof(serverAddr));//serverAddr 0으로 다 밀어버리기
	serverAddr.sin_family = AF_INET;//IPv4
	::inet_pton(AF_INET, "192.168.0.9", &serverAddr.sin_addr);//127.0.01 => Loop back : 자기 PC의 주소
	serverAddr.sin_port = ::htons(7777); //1~1000 사이 포트는 건들면 안됨
	//네트워크 정수 표현 => 빅엔디언

	//3. 연결
	if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Connect ErrorCode : " << errCode << endl;
		return 0;
	}

	while (true)
	{
		//... 서버에서 들어온 데이터 분석, 혹은 클라이언트 코드 실행
		this_thread::sleep_for(1s);
	}

	//소켓 리소스 반환 및 윈속 종료
	::closesocket(clientSocket);
	::WSACleanup();
}
