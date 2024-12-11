#pragma once
#include "Session.h"
#include "Room.h"

extern Room* G_Room;

class GameSession : public PacketSession
{
public:
	GameSession();
	~GameSession();

	virtual void OnConnected() override;
	virtual int32 OnRecvPacket(BYTE* buffer, int32 len)override;
	virtual void OnSend(int32 len) override;
	virtual void Disconnected() override;

	weak_ptr<class ChatPlayer> _curPlayer;
};

