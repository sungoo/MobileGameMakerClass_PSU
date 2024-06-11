#pragma once

class Knight
{
public:
	Knight();
	Knight(int hp);
	~Knight();

	void PrintInfo();

	void AddHp(int value);
	bool IsDead();

	int GetAttackDamage();

	void OnDamaged(Knight* attacker, bool isAgainst);

public:
	int _hp;
	int _maxHp;
	int _attack;
};

