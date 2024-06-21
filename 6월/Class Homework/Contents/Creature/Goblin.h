#pragma once
#include "Monster.h"
class Goblin :public Monster
{
public:
	Goblin(string name, string major, int hp, int atk, int exp);
	virtual ~Goblin();
};

