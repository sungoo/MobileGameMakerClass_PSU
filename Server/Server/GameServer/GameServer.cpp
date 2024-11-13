#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#include "Serviece.h"

class GameSession : public Session
{
public:
	GameSession()
	{
		string temp = "Hello Client!! I'm Server!!";
		memcpy(_sendBuffer, temp.data(), temp.size());
	}

	~GameSession()
	{
		cout << "Session Disconnected" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "클라이언트가 서버에 접속 성공!!" << endl;
		Send(reinterpret_cast<BYTE*>(_sendBuffer), 1000);
	}

	virtual int32 OnRecv(BYTE* buffer, int32 len)
	{
		char* str = reinterpret_cast<char*>(buffer);

		cout << "Recv : " << str << endl;

		this_thread::sleep_for(1s);
		Send(reinterpret_cast<BYTE*>(_sendBuffer), 1000);

		return len;
	}

	virtual void OnSend(int32 len) override
	{
		cout << "Send 성공" << endl;
	}

	virtual void Disconnected() override
	{
		cout << "Disconnected" << endl;
	}
};

int main()
{
	// IOCP
	// 1. CP(Completion Port)에 Socket을 등록
	//
	CoreGlobal::Create();

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