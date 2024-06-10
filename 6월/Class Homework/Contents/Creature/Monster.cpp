#include "pch.h"
#include "Monster.h"

Monster::Monster(string name, int hp, int afk):
	Creature(name, hp, afk)
{
}

Monster::~Monster()
{
}

void Monster::Attack(Creature* other)
{
	this->Creature::PreAttack(other);

	other->Damaged(atk);
}
