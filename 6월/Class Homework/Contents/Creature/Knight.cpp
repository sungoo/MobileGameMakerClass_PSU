#include "pch.h"
#include "Knight.h"

Knight::Knight(string name, int hp, int afk):
Player(name, hp, afk)
{
}

Knight::~Knight()
{
}

void Knight::Attack(Creature* other)
{
	this->Creature::PreAttack(other);
	float ratio = (float)cur_hp / (float)MaxHP;

	if (ratio < 0.5f) {
		//현재 체력 50% 미만
		other->Damaged(atk * 2);
	}
	else {
		other->Damaged(atk);
	}
}
