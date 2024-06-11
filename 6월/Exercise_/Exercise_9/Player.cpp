#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() : _hp(100), _maxHp(100), _attack(10)
{

}


Player::Player(int hp) : _hp(hp), _maxHp(hp), _attack(10)
{
	
}

Player::~Player()
{
	
}


void Player::AddHp(int value)
{
	_hp += value;
	if (_hp < 0)
		_hp = 0;
	if (_hp > _maxHp)
		_hp = _maxHp;
}

bool Player::IsDead()
{
	return (_hp <= 0);
}

int Player::GetAttackDamage()
{
	int damage = _attack;

	if (_maxHp > 0)
	{
		int percentage = (100 * _hp) / _maxHp;
		if (percentage <= 50)
			damage *= 2;
	}

	return damage;
}

void Player::PrintInfo()
{
	cout << "------ PlayerInfo ------" << endl;
	cout << "HP: " << _hp << endl;
	cout << "ATT: " << _attack << endl;
}

void Player::OnDamaged(Player* attacker)
{
	if (attacker == nullptr)
		return;
	if (IsDead())
		return;

	// 내 체력 깎는다
	int damage = attacker->GetAttackDamage();
	AddHp(-damage);

	// 반격!
	attacker->OnDamaged(this);
}