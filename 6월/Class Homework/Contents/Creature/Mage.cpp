#include "pch.h"
#include "Mage.h"

Mage::Mage(string name, string major, int hp, int mp, int atk):
	Player(name, major, hp, atk),
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

void Mage::printInfo()
{
	cout << "--------------상태---------------" << endl;
	cout << "이름 : " << name << endl;
	cout << "클래스 : " << major << endl;
	cout << "체력 : " << cur_hp << endl;
	cout << "공격력 : " << atk << endl;
	cout << "마력 : " << mp << endl;
	cout << "---------------------------------" << endl;
}
