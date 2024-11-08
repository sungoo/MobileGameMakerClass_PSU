#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#include "Serviece.h"

int main()
{
	// IOCP
	// 1. CP(Completion Port)에 Socket을 등록
	//
	CoreGlobal::Create();

	shared_ptr<ServerService> service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<Session>,
		100
	);

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