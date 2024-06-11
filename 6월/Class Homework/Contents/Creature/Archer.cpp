#include "pch.h"
#include "Archer.h"

Archer::Archer(string name, int hp, int afk) :
	Player(name, hp, afk)
{
}

Archer::~Archer()
{
}

void Archer::Attack(Creature* other)
{
	this->Creature::PreAttack(other); //맴버함수 호출 조건 : 객체가 항상 있어야함
	int crit = rand() % 10;
	float ratio = crit / (float)100;

	if (ratio < 0.3f) {
		cout << "크리티컬! ";
		other->Damaged(atk * 3);
	}
	else {
		other->Damaged(atk);
	}
}
