#include "pch.h"
#include "Mage.h"

Mage::Mage(string name, string major, int hp, int mp, int atk):
	Player(name, major, hp, atk),
	MaxMP(mp)
{
	cur_mp = MaxMP;
}

Mage::~Mage()
{
}

void Mage::Attack(Creature* other)
{
	if (cur_mp < 5) {
		cout << "-------------------------\n" << name << "의 마나가 부족합니다. 공격을 한 턴 쉽니다." << endl;
		cur_mp += 50;
	}

	this->Creature::PreAttack(other);

	cur_mp -= 5;
	other->Damaged(atk);
}

void Mage::printInfo()
{
	cout << "--------------상태---------------" << endl;
	cout << "이름 : " << name << endl;
	cout << "클래스 : " << major << endl;
	cout << "체력 : " << cur_hp << endl;
	cout << "공격력 : " << atk << endl;
	cout << "마력 : " << cur_mp << endl;
	cout << "---------------------------------" << endl;
}

void Mage::Revival()
{
	cur_hp = MaxHP;
	cur_mp = MaxMP;
}
