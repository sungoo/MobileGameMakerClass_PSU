#pragma once

class ChatPlayer;

class Room
{
public:
	void Enter(shared_ptr<ChatPlayer> player);
	void Leave(shared_ptr<ChatPlayer> player);
	void BroadCast(shared_ptr<SendBuffer> sendBuff);

private:
	USE_LOCK;

	HashTable<uint64, weak_ptr<ChatPlayer>> _playerTable;
};