#include "pch.h"
#include "Creature.h"

Creature::Creature(string name, string major, int Max_hp, int afk) :
	name(name), major(major), MaxHP(Max_hp), atk(afk)
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
	cout << "클래스 : " << major << endl;
	cout << "체력 : " << cur_hp << endl;
	cout << "공격력 : " << atk << endl;
	cout << "---------------------------------" << endl;
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

void Creature::Revival()
{
	cur_hp = MaxHP;
}

string Creature::getName()
{
	return name;
}

string Creature::getMajor()
{
	return major;
}

int Creature::getM_hp()
{
	return MaxHP;
}

int Creature::getC_hp()
{
	return cur_hp;
}

int Creature::getAtk()
{
	return atk;
}

