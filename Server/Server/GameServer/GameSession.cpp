#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"

GameSession::GameSession()
{
	
}

GameSession::~GameSession()
{
	cout << "Session Disconnected" << endl;
}

void GameSession::OnConnected()
{
	{//입장하면 입장해있던 모든 클라이언트에게 입장했다고 방송고지
		shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(100);
		string temp = "Client entered!";
		buf->CopyData((void*)temp.data(), temp.size());

		G_GameSessionManager->BroadCast(buf);
	}
	G_GameSessionManager->Add(static_pointer_cast<GameSession>(shared_from_this()));
	
	shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(100);
	string temp = "Hello Client!";
	
	//Packet Session
	BYTE* buffer = buf->Buffer();
	((PacketHeader*)buffer)->id = 1;//id = 1이면 Hello MSG
	((PacketHeader*)buffer)->size = (sizeof(temp) + sizeof(PacketHeader));
	//Packet Content
	buf->CopyData_Packet((BYTE*)temp.data(), sizeof(temp));
	G_GameSessionManager->BroadCast(buf);
	G_GameSessionManager->Add(static_pointer_cast<GameSession>(shared_from_this()));
}

int32 GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader header = *((PacketHeader*)buffer);

	cout << "Packet ID : " << header.id << " Size : " << header.size << endl;

	return len;
}

void GameSession::OnSend(int32 len)
{
	cout << "Send 성공" << endl;
}

void GameSession::Disconnected()
{
	G_GameSessionManager->Remove(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "Disconnected" << endl;
}
