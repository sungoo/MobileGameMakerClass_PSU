#pragma once
#include "Monster.h"

struct DamageTable {
	int _totalDamage = 0;
	Creature* _who = nullptr;
};
class HopGoblin :public Monster
{
	vector<DamageTable> _DamageRate;

public:
	HopGoblin(string name, string major, int hp, int atk, int exp);
	virtual ~HopGoblin();
};

