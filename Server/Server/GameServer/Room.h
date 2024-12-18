#pragma once

class ChatPlayer;

class Room
{
public:
	void Enter(shared_ptr<ChatPlayer> player);
	void Leave(shared_ptr<ChatPlayer> player);
	void BroadCast(shared_ptr<SendBuffer> sendBuff);
	string GetPlayerName(uint64 id);

private:
	USE_LOCK;

	HashTable<uint64, shared_ptr<ChatPlayer>> _playerTable;
};