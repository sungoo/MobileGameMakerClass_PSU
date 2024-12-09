#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "Protocol.pb.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case 0:
		break;
	case C_PLAYER_INFO:
		Handle_S_PlayerInfo(buffer, len);
		break;

	default:
		break;
	}
}

// => Header[4] [1, 100, 10, 2, 사랑니, 1.0, 마취, 2.0]
// 
// 
// Player Id : 1 / hp : 100 / atk : 10 / buff : [사랑니, 1.0] [마취, 2.0]
void ClientPacketHandler::Handle_S_PlayerInfo(BYTE* buffer, int32 len)
{
	/*BufferReader br(buffer, len);

	PlayerInfo_Packet* pkt = reinterpret_cast<PlayerInfo_Packet*>(buffer);

	if (pkt->IsValid() == false)
		return;

	PacketList<BuffData> buffDatas = pkt->GetBuffList();

	cout << "BuffCount : " << buffDatas.size() << endl;
	
	for (auto buff : buffDatas)
	{
		cout << "Buff ID : " << buff.buffId << " / BuffRemain" << buff.remainTime << endl;
	
		PlayerInfo_Packet::VictimList victims = pkt->GetVictimList(&buff);
		cout << "victim count : " << buff.victimCount << endl;
		for (auto& victim : victims)
		{
			cout << "Victim : " << victim << endl;
		}
	}

	PacketList<WCHAR> wCharList = pkt->GetWCharList();
	wcout << (WCHAR)wCharList[0] << endl;*/

	Protocol::S_PlayerInfo pkt;

	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	cout << "ID : " << pkt.id() << " / HP : " << pkt.hp() << " / ATK : " << pkt.atk() << endl;
	cout << "Buffs Size : " << pkt.buffs_size() << endl;

	for (auto& buff : pkt.buffs())
	{
		cout << "Buff ID : " << buff.buffid() << endl;
		cout << "Remain Time : " << buff.remaintime() << endl;
		cout << "Victims Size : " << buff.victims_size() << endl;

		for (auto& victim : buff.victims())
		{
			cout << "Victim ID : " << victim << endl;
		}
		cout << endl;
	}
}

shared_ptr<SendBuffer> ClientPacketHandler::Make_C_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs, wstring name)
{
	/*shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(1000);
	PlayerInfo_Packet p;
	p.id = id;
	p.hp = hp;
	p.atk = atk;

	BufferWriter bw(buf->Buffer(), buf->Capacity());

	PacketHeader* header = bw.Reserve<PacketHeader>();
	header->id = S_SERVER_INFO;
	header->size = (sizeof(p) + sizeof(PacketHeader));
	bw << p;

	buf->Ready(bw.WriteSize());*/

	return nullptr;
}