#include "pch.h"
#include "Monster.h"

Monster::Monster(string name, string major, int hp, int afk):
	Creature(name, major, hp, afk)
{
}

Monster::Monster(string name, string major, int hp, int atk, int exp):
	Creature(name, major, hp, atk), _exp(exp)
{
}

Monster::~Monster()
{
}

int Monster::GetEXP()
{
	return _exp;
}

void Monster::Attack(Creature* other)
{
	this->Creature::PreAttack(other);

	other->Damaged(atk);
}
