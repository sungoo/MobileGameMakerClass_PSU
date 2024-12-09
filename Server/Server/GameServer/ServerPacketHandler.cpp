#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"


void ServerPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	//TODO : Recv했을 때 패킷 파싱하고 분석
	BufferReader br(buffer, len);
	
	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case 0:
		break;
	case C_PLAYER_INFO:
		Handle_S_Test(buffer, len);
		break;

	default:
		break;
	}
}

void ServerPacketHandler::Handle_S_Test(BYTE* buffer, int32 len)
{
	//TODO
	return;
}

shared_ptr<SendBuffer> ServerPacketHandler::MakeSendBuffer(Protocol::S_PlayerInfo& pkt)
{
	return _MakeSendBuffer<Protocol::S_PlayerInfo>(pkt, S_PLAYER_INFO);
}
