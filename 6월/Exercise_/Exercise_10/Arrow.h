#pragma once

class Player;

class Arrow
{
public:
	Arrow(Player* target, int damage);
	~Arrow();

public:
	void AttackTarget();

public:
	Player* _target;
	int _damage;
};

