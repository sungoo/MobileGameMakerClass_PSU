#include "pch.h"
#include "Monster.h"

Monster::Monster(string name, string major, int hp, int afk):
	Creature(name, major, hp, afk)
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
