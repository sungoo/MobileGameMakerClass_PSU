#pragma once


class ChatPlayer
{
public:
	string name;
	int64 id;
	int32 hp;
	int32 atk;

	shared_ptr<class ServerSession> _session;
};