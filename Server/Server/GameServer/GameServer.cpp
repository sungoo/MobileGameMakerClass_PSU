#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#include "Serviece.h"
#include "GameSession.h"
#include "GameSessionManager.h"

// GameSession : 서버에서 클라이언트가 접속하면 안내할 식탁
// GameSessionManager : 모든 클라이언트가 앉았는 식탁들을 관리하는 수단

int main()
{
	// IOCP
	// 1. CP(Completion Port)에 Socket을 등록
	//
	CoreGlobal::Create();
	G_GameSessionManager = new GameSessionManager();

	shared_ptr<ServerService> service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,
		100
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

	while (true)
	{
		
	}

	TM_M->Join();

	//SocketUtility::Clear();

	CoreGlobal::Delete();

	return 0;
}