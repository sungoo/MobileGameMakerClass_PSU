#include "Knight.h"
#include <iostream>
using namespace std;

// [사양서] 기본값 Hp=100, Attack=10
Knight::Knight() : _hp(100), _maxHp(100), _attack(10)
{

}

Knight::Knight(int hp) : _hp(hp), _maxHp(hp), _attack(10)
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
	if (_hp > _maxHp)
		_hp = _maxHp;
}

bool Knight::IsDead()
{
	return (_hp <= 0);
}

int Knight::GetAttackDamage()
{
	// hp 50% 이하 => maxHp / hp가 2 이상
	int damage = _attack;

	float ratio = static_cast<float>(_hp) / static_cast<float>(_maxHp);
	//부동소수점
	//(부호)(지수부)(유효숫자)...부동소수점의 오차 ... 오차때문에 float은 ==을 잘 쓰지 않음.
	if (ratio <= 0.5f)
		damage *= 2;

	return damage;
}

void Knight::PrintInfo()
{
	cout << "HP: " << _hp << endl;
	cout << "ATT: " << _attack << endl;
}