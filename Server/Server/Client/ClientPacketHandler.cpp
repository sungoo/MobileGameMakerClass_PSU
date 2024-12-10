#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "Protocol.pb.h"

void ClientPacketHandler::HandlePacket(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case 0:
		break;
	case C_PLAYER_INFO:
		Handle_S_PlayerInfo(session, buffer, len);
		break;

	default:
		break;
	}
}

// => Header[4] [1, 100, 10, 2, 사랑니, 1.0, 마취, 2.0]
// 
// 
// Player Id : 1 / hp : 100 / atk : 10 / buff : [사랑니, 1.0] [마취, 2.0]
void ClientPacketHandler::Handle_S_PlayerInfo(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
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

shared_ptr<SendBuffer> ClientPacketHandler::MakeSendBuffer(Protocol::C_PlayerInfo& pkt)
{
	return _MakeSendBuffer(pkt, PacketID::C_PLAYER_INFO);
}