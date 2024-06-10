#include "pch.h"
#include "Creature.h"

Creature::Creature(string name, int hp, int afk) :
	name(name), cur_hp(hp), atk(afk)
{
}

Creature::~Creature()
{
}

void Creature::printInfo()
{
	cout << "--------------상태---------------" << endl;
	cout << "이름 : " << name << endl;
	cout << "체력 : " << cur_hp << endl;
	cout << "공격력 : " << atk << endl;
}

void Creature::Damaged(int amount)
{
	cur_hp -= amount;

	cout << name << "에게 " << amount << "데미지!!" << endl;

	if (cur_hp < 0)
		cur_hp = 0;

	printInfo();

	if (IsDead()) {
		cout << name << "이 사망했습니다." << endl;
	}
}

void Creature::PreAttack(Creature* other)
{
	cout << name << "이 " << other->name << "에게 공격을 시도합니다." << endl;
}

