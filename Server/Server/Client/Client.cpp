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

class ServerSession : public PacketSession
{
public:
	ServerSession()
	{
	}

	~ServerSession()
	{
		cout << "Session Disconnected" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "Server 에 접속 성공!!" << endl;

		/*shared_ptr<SendBuffer> sendBuf = make_shared<SendBuffer>(100);
		string temp = "Hello Server~!! I'm Client!";
		sendBuf->CopyData((void*)temp.data(), temp.size());
		Send(sendBuf);*/
	}

	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) override
	{
		PacketHeader header = *((PacketHeader*)buffer);

		cout << "Packet ID : " << header.id << " Size : " << header.size << endl;

		char recvData[100];
		::memcpy(recvData, buffer + 4, header.size);

		cout << recvData << endl;

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

	while (true)
	{

	}

	TM_M->Join();

	//SocketUtility::Clear();

	CoreGlobal::Delete();
}
