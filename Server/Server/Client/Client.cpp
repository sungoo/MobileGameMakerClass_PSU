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

#include "Serviece.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "ServerSession.h"

ChatPlayer G_Player;

int main()
{
	this_thread::sleep_for(1s);
	
	CoreGlobal::Create();

	shared_ptr<ClientService> service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>,
		1
	);

	service->Start();

	for (int i = 0; i < 5; i++)
	{
		TM_M->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}
	//5초 대기 : 서버에 EnterRoom하기 전에 메시지 패킷을 보내면 안된다.
	//=>5초 안에 PlayerInfo pkt를 날려줘야한다.
	this_thread::sleep_for(60s);

	cout << "메세지를 입력하세요. : ";

	//main
	while (true)
	{
		string sendMsg;

		//cin >> sendMsg; // block, 동기
		std::getline(std::cin, sendMsg);// non-block, 비동기

		Protocol::C_ChatMsg sendbuf;
		sendbuf.set_id(G_Player.id);
		sendbuf.set_msg(sendMsg);

		auto sendbuffer = ClientPacketHandler::MakeSendBuffer(sendbuf);
		service->BroadCast(sendbuffer);//client에서 broadcast해도 server밖에 없음
	}

	TM_M->Join();

	//SocketUtility::Clear();

	CoreGlobal::Delete();
}
