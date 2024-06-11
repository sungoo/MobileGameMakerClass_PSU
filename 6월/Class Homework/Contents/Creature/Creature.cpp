#include "pch.h"
#include "Creature.h"

Creature::Creature(string name, int Max_hp, int afk) :
	name(name), MaxHP(Max_hp), atk(afk)
{
	cur_hp = Max_hp;
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

