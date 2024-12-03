#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"


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
	case S_TEST:
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

// Player Id : 1 / hp : 100 / atk : 10 / buff : [사랑니, 1.0] [마취, 2.0]
// => Header[4] [1, 100, 10, 2, 사랑니, 1.0, 마취, 2.0]
shared_ptr<SendBuffer> ServerPacketHandler::Make_S_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs, wstring name)
{
	shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(1000);
	PlayerInfo_Packet p;
	p.id = id;
	p.hp = hp;
	p.atk = atk;
	//p.buffs = buffs;

	BufferWriter bw(buf->Buffer(), buf->Capacity());
	//Header Reserve, packet 아이디 설정
	PacketHeader* header = bw.Reserve<PacketHeader>();
	
	bw << id << hp << atk;

	struct VectorHeader
	{
		uint32 offset;
		uint32 count;
	};

	VectorHeader* buffHeader = bw.Reserve<VectorHeader>();
	VectorHeader* nameHeader = bw.Reserve<VectorHeader>();

	buffHeader->offset = bw.WriteSize();
	buffHeader->count = buffs.size();

	//버프 배열 작성
	for (BuffData& data : buffs)
	{
		bw << data.buffId << data.remainTime;
	}
	
	nameHeader->offset = bw.WriteSize();
	nameHeader->count = name.size();

	for (WCHAR c : name)
	{
		bw << c;
	}

	header->id = S_TEST;
	header->size = bw.WriteSize();
	
	//출하준비완료
	buf->Ready(bw.WriteSize());

	return buf;
}
