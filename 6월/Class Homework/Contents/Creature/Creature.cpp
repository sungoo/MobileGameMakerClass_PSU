#include "pch.h"
#include "Creature.h"

Creature::Creature(string name, string major, int Max_hp, int afk) :
	name(name), major(major), BaseHP(Max_hp), BaseATK(afk), isActive(true)
{
	MaxHP = BaseHP;
	cur_hp = Max_hp;
	atk = BaseATK;
}

Creature::~Creature()
{
}

void Creature::Init()
{
	cur_hp = MaxHP;
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

void Creature::Damaged(int amount, Creature* attacker = nullptr)
{
	cur_hp -= amount;

	if (attacker != nullptr && dynamic_cast<Monster*>(this) != nullptr) {
		Player* p = dynamic_cast<Player*>(attacker);
		if (p != nullptr) {
			p->GainExp(_giveExp);
			p->LevelUp();
		}
	}

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

bool Creature::IsDead()
{
	return cur_hp <= 0;
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

