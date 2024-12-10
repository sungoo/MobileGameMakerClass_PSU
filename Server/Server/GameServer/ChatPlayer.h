#pragma once
class ChatPlayer
{
public:
	uint64 playerId;
	string name;
	uint32 hp;
	uint16 atk;
	weak_ptr<class GetNamedPipeClientSessionId> _ownerSession;
};

