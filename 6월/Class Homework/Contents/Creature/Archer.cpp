#include "pch.h"
#include "Archer.h"

Archer::Archer(string name, string major, int hp, int afk) :
	Player(name, major, hp, afk), critRate(0.3f)
{
}

Archer::~Archer()
{
}

void Archer::Attack(Creature* other)
{
	this->Creature::PreAttack(other); //맴버함수 호출 조건 : 객체가 항상 있어야함
	int crit = rand() % 30;
	float ratio = static_cast<float>(crit) / static_cast<float>(100);

	if (ratio < critRate) {
		cout << "크리티컬! ";
		other->Damaged(atk * 3, this);
	}
	else {
		other->Damaged(atk, this);
	}
}

void Archer::printInfo()
{
	cout << "--------------상태---------------" << endl;
	cout << "이름 : " << name << endl;
	cout << "클래스 : " << major << endl;
	cout << "체력 : " << cur_hp << endl;
	cout << "공격력 : " << atk << endl;
	cout << "치명타율 : " << critRate << endl;
	cout << "---------------------------------" << endl;
}
