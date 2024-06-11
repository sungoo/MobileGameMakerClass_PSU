#include "Knight.h"
#include <iostream>
using namespace std;

// [사양서] 기본값 Hp=100, Attack=10
Knight::Knight() : _hp(100), _attack(10)
{

}

Knight::Knight(int hp) : _hp(hp), _attack(10)
{

}

Knight::~Knight()
{

}

void Knight::AddHp(int value)
{
	_hp += value;

	if (_hp < 0)
		_hp = 0;
}

bool Knight::IsDead()
{
	return (_hp <= 0);
}

void Knight::PrintInfo()
{
	cout << _hp << endl;
	cout << _attack << endl;
}