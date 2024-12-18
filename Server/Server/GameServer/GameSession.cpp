#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"
#include "Protocol.pb.h"

GameSession::GameSession()
{
	
}

GameSession::~GameSession()
{
	cout << "Session Disconnected" << endl;
}

void GameSession::OnConnected()
{
	G_GameSessionManager->Add(static_pointer_cast<GameSession>(shared_from_this()));
}

int32 GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader header = *((PacketHeader*)buffer);

	cout << "Packet ID : " << header.id << " Size : " << header.size << endl;

	ServerPacketHandler::HandlePacket(static_pointer_cast<PacketSession>(shared_from_this()), buffer, len);

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
