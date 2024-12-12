#pragma once
#include "Protocol.pb.h"

template<typename T, typename C>
class PacketList_Iterator
{
public:
	PacketList_Iterator(C& container, uint16 index):_container(container), _index(index){}

	bool operator!=(const PacketList_Iterator& other) { return _index != other._index; }
	const T& operator*()const { return _container[_index]; }
	T& operator*() { return _container[_index]; }
	T* operator->() { return &_container[_index]; }
	PacketList_Iterator& operator++() { _index++; return *this; }
	PacketList_Iterator  operator++(int32) { PacketList_Iterator temp = *this; _index++; return temp; }

private:
	C& _container;
	uint16 _index;
};

template <typename T>
class PacketList
{
public:
	PacketList() : _data(nullptr), _count(0) {}
	PacketList(T* data, uint16 count) : _data(data), _count(count) {}

	T& operator[](uint16 index)
	{
		ASSERT_CRASH(index < _count);
		return _data[index];
	}

	uint16 size() { return _count; }
	PacketList_Iterator<T, PacketList<T>> begin() { return PacketList_Iterator<T, PacketList<T>>(*this, 0);}
	PacketList_Iterator<T, PacketList<T>> end(){return PacketList_Iterator<T, PacketList<T>>(*this, _count);}

private:
	T* _data;
	uint16 _count;
};

//규약
enum PacketID
{
	NONE,
	S_PLAYER_INFO = 1,
	S_ENTEROOM = 2,
	S_CHATMSG = 3,

	C_PLAYER_INFO = 101,
	C_CHATMSG = 102,
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

	//vector<int32> victims;
	uint32 victimOffset;
	uint32 victimCount;

	bool Validate(BYTE* packetStart, uint16 packetSize, OUT uint32 size)
	{
		if (victimOffset + victimCount * sizeof(int32) > packetSize)
			return false;

		size += victimCount * sizeof(int32);
		return true;
	}
};

#pragma pack(1)
struct PlayerInfo_Packet
{
	PacketHeader header;

	int64 id;
	int32 hp;
	int16 atk;
	
	//vector<BuffData> buffs;
	//wstring name;
	//=>
	uint32 buffOffset;//배열이 시작하는 메모리 offset
	uint32 buffCount;

	uint32 wCharOffset;
	uint32 wCharCount;

	bool IsValid()
	{
		uint32 size = 0;
		size += sizeof(PlayerInfo_Packet);
		if (header.size < size)//그냥 이상함
			return false;
		size += buffCount * sizeof(BuffData);

		PacketList<BuffData> buffList = GetBuffList();
		for (int i = 0; i < buffList.size(); i++)
		{
			if (buffList[i].Validate(reinterpret_cast<BYTE*>(this), header.size, OUT size) == false)
				return false;
		}

		size += wCharCount * sizeof(WCHAR);

		//기입한 크기가 실제 패킷크기랑 동일
		if (size != header.size)
			return false;

		// 흘러넘치게 들어왔다 => 뭔가 이상함
		if (wCharOffset + wCharCount * sizeof(WCHAR) > header.size)
			return false;

		return true;
	}

	using BuffList = PacketList<BuffData>;
	using Name = PacketList<WCHAR>;
	using VictimList = PacketList<int32>;

	BuffList GetBuffList()
	{
		//그냥 this에 포인터 덧셈을 해버리면 PlayerInfo_Packet의 크기만큼 덧셈이 되어버려서,
		//BYTE* 형으로 바꾸고 계산해주는게 필요하다.
		BYTE* data = reinterpret_cast<BYTE*>(this);
		data += buffOffset;
		return BuffList(reinterpret_cast<BuffData*>(data), buffCount);
	}

	VictimList GetVictimList(BuffData* buff)
	{
		BYTE* data = reinterpret_cast<BYTE*>(this);
		data += buff->victimOffset;

		return VictimList(reinterpret_cast<int32*>(data), buff->victimCount);
	}

	Name GetWCharList()
	{
		WCHAR* data = reinterpret_cast<WCHAR*>(this);
		data += wCharOffset;
		return Name(reinterpret_cast<WCHAR*>(data), wCharCount);
	}
};
#pragma pack()

//

class ClientPacketHandler
{
public://Packet형태로 들어왔을 때 -> Recv했을 때 처리 방법
	static void HandlePacket(shared_ptr<PacketSession> session, BYTE* buffer, int32 len);

	static void Handle_S_PlayerInfo(shared_ptr<PacketSession> session, BYTE* buffer, int32 len);
	static void Handle_S_EnterRoom(shared_ptr<PacketSession> session, BYTE* buffer, int32 len);
	static void Handle_S_ChatMsg(shared_ptr<PacketSession> session, BYTE* buffer, int32 len);

	//Packet형태로 Sendbuffer 만들기
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_PlayerInfo& pkt);
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::C_ChatMsg& pkt);
};

template<typename T>
shared_ptr<SendBuffer> _MakeSendBuffer(T& pkt, uint16 pktId)
{
	//공용 header 만들기
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	header->id = pktId;
	header->size = packetSize;

	ASSERT_CRASH(pkt.SerializeToArray(&(header[1]), dataSize));

	sendBuffer->Ready(packetSize);
	return sendBuffer;
}