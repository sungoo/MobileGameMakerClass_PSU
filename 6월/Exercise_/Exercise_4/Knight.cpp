#include "Knight.h"
#include <iostream>
using namespace std;

// [사양서] 기본값 Hp=100, Attack=10
Knight::Knight() : _currHp(100), _attack(10), _maxHP(1000)
{

}

Knight::Knight(int hp) : _currHp(hp), _attack(10), _maxHP(1000)
{

}

Knight::~Knight()
{

}

void Knight::AddHp(int value)
{
	_currHp += value;

	if (_currHp > _maxHP)
		_currHp = _maxHP;
}

bool Knight::IsDead()
{
	return (_currHp <= 0);
}

void Knight::PrintInfo()
{
	cout << "HP: " << _currHp << endl;
	cout << "ATT: " << _attack << endl;
}