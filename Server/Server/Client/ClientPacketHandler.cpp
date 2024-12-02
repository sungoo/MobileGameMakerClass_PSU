#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case 0:
		break;
	case S_TEST:
		Handle_C_Test(buffer, len);
		break;

	default:
		break;
	}
}

// => Header[4] [1, 100, 10, 2, 사랑니, 1.0, 마취, 2.0]
// 
// 
// Player Id : 1 / hp : 100 / atk : 10 / buff : [사랑니, 1.0] [마취, 2.0]
void ClientPacketHandler::Handle_C_Test(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PlayerInfo_Protocol pkt;
	br >> pkt;
	//id 고정(S_TEST)
	//size 고정(18byte)

	if (pkt.IsValid() == false)
		return;

	vector<BuffData> buffDatas;
	buffDatas.resize(pkt.buffCount);
	for (int i = 0; i < pkt.buffCount; i++)
	{
		br >> buffDatas[i];
	}

	wstring name;
	name.resize(pkt.nameCount);
	for (int i = 0; i < pkt.nameCount; i++)
	{
		br >> name;
	}

	wcout.imbue(std::locale("kor"));
	wcout << name << endl;

	cout << "BuffCount : " << buffDatas.size() << endl;
	for (auto buff : buffDatas)
	{
		cout << "Buff ID : " << buff.buffId << " / BuffRemain" << buff.remainTime << endl;
	}
}

shared_ptr<SendBuffer> ClientPacketHandler::Make_C_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs, wstring name)
{
	shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(1000);
	PlayerInfo_Protocol p;
	p.id = id;
	p.hp = hp;
	p.atk = atk;

	BufferWriter bw(buf->Buffer(), buf->Capacity());

	PacketHeader* header = bw.Reserve<PacketHeader>();
	header->id = S_TEST;
	header->size = (sizeof(p) + sizeof(PacketHeader));
	bw << p;

	buf->Ready(bw.WriteSize());

	return buf;
}
