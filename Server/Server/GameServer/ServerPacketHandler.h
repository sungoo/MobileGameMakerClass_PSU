#pragma once

//규약
enum PacketID
{
	NONE,
	S_TEST = 1,
};

enum BuffID
{
	BUFF_NONE,
	BUFF_LOVE = 1,
	BUFF_ANESTHESIA = 2
};

struct BuffData
{
	uint32 buffId;
	float remainTime;
};

struct PlayerInfo_Protocol
{
	PacketHeader header;

	int64 id; //8
	int32 hp; //4
	int16 atk;//2
	int16 padding = -1;
					// = 16 byte
	uint32 buffOffset;
	uint32 buffCount;

	uint32 nameOffset;
	uint32 nameCount;

	bool IsValid()
	{
		uint32 size = 0;
		size += sizeof(PlayerInfo_Protocol);
		size += buffCount * sizeof(BuffData);
		size += nameCount * sizeof(WCHAR);

		//기입한 크기가 실제 패킷크기랑 동일
		if (size != header.size)
			return false;

		// 흘러넘치게 들어왔다 => 뭔가 이상함
		if (nameOffset + nameCount * sizeof(WCHAR) > header.size)
			return false;

		return true;
	}
};

class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, int32 len);

	static shared_ptr<SendBuffer> Make_S_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs, wstring name);
};

