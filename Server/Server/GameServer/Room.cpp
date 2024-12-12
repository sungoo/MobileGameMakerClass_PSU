#include "pch.h"
#include "Room.h"
#include "ChatPlayer.h"
#include "GameSession.h"

void Room::Enter(shared_ptr<ChatPlayer> player)
{
	WRITE_LOCK;//자료구조에 접근할 때 보통 Lock을 잡는다.(지금은 공유데이터 G_Room)
	_playerTable[player->playerId] = player;
}

void Room::Leave(shared_ptr<ChatPlayer> player)
{
	WRITE_LOCK;
	_playerTable.erase(player->playerId);
}

void Room::BroadCast(shared_ptr<SendBuffer> sendBuff)
{
	WRITE_LOCK;

	for (auto& p : _playerTable)
	{
		p.second.lock()->_ownerSession.lock()->Send(sendBuff);
	}
}

string Room::GetPlayerName(uint64 id)
{
	if (_playerTable.count(id) == 0) { return string("알 수 없는 아이디"); }
	return _playerTable[id].lock()->name;
}
