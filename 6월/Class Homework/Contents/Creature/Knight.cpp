#include "pch.h"
#include "Knight.h"

Knight::Knight(string name, string major, int hp, int afk):
Player(name, major, hp, afk), furi(false)
{
}

Knight::~Knight()
{
}

void Knight::Attack(Creature* other)
{
	this->Creature::PreAttack(other);
	float ratio = (float)cur_hp / (float)MaxHP;

	if (ratio < 0.5f)
		furi = true;
	else
		furi = false;

	if (furi) {
		//현재 체력 50% 미만
		other->Damaged(atk * 2);
	}
	else {
		other->Damaged(atk);
	}
}

void Knight::printInfo()
{
	cout << "--------------상태---------------" << endl;
	cout << "이름 : " << name << endl;
	cout << "클래스 : " << major << endl;
	cout << "체력 : " << cur_hp << endl;
	cout << "공격력 : " << atk << endl;
	if (furi) cout << "광전사 모드!" << endl;
	cout << "---------------------------------" << endl;
}
