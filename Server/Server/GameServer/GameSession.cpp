#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"

GameSession::GameSession()
{
	
}

GameSession::~GameSession()
{
	cout << "Session Disconnected" << endl;
}

void GameSession::OnConnected()
{
	vector<BuffData> buffs;
	buffs.push_back({ 1, 48.0f });
	buffs.push_back({ 2,2.0f });
	wstring name = L"엉덩이";

	///////////////////////
	///   Packet 제작   ///
	///////////////////////

	PKT_S_TEST_WRITE pkt_writer(1234, 10, 5);
	auto buffList = pkt_writer.ReserveBuffList(buffs.size());
	auto victimList0 = pkt_writer.ReserveVictimList(&buffList[0], 2);
	auto victimList1 = pkt_writer.ReserveVictimList(&buffList[1], 4);

	auto wCharList = pkt_writer.ReserveWCHARList(name.size());

	for (int i = 0; i < buffs.size(); i++)
	{
		buffList[i].buffId = buffs[i].buffId;
		buffList[i].remainTime = buffs[i].remainTime;
	}
	{
		victimList0[0] = 100;
		victimList0[1] = 101;

		victimList1[0] = 0614;
		victimList1[1] = 0622;
		victimList1[2] = 1109;
		victimList1[3] = 1211;
	}
	for (int i = 0; i < wCharList.size(); i++)
	{
		wCharList[i] = name[i];
	}

	//shared_ptr<SendBuffer> sendbuffer = ServerPacketHandler::Make_S_TEST(1234, 10, 5, buffs, name);
	G_GameSessionManager->BroadCast(pkt_writer.Ready());

	G_GameSessionManager->Add(static_pointer_cast<GameSession>(shared_from_this()));
}

int32 GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader header = *((PacketHeader*)buffer);

	cout << "Packet ID : " << header.id << " Size : " << header.size << endl;

	ServerPacketHandler::HandlePacket(buffer, len);

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
