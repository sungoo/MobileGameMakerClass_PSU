#include "pch.h"
#include "Mage.h"

Mage::Mage(string name, int hp, int mp, int atk):
	Player(name, hp, atk),
	mp(mp)
{
}

Mage::~Mage()
{
}

void Mage::Attack(Creature* other)
{
	if (mp < 5) {
		cout << "-------------------------\n" << name << "의 마나가 부족합니다. 공격을 한 턴 쉽니다." << endl;
		mp += 50;
	}

	this->Creature::PreAttack(other);

	mp -= 5;
	other->Damaged(atk);
}
