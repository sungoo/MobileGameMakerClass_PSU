#include "pch.h"
#include "Player.h"

Player::Player(string name, string major, int hp, int afk):
	Creature(name, major, hp, afk),
	_currExp(0)
{
}

Player::Player(string name, string major, int hp, int afk, int Lv):
	Creature(name, major, hp, afk),
	_currExp(0), _Lv(Lv)
{
}

Player::~Player()
{
}

void Player::GainExp(int much)
{
	if (much <= 0)
		return;
	_currExp += much;
}

void Player::LevelUp()
{
	if (_currExp < 100)
		return;
	int gainLevel = _currExp / 100;
	int leftExp = _currExp % 100;

	cout << name << "이(가) 레벨 업!\n레벨 : " << _Lv << " -> ";

	_Lv += gainLevel;
	_currExp = leftExp;

	cout << _Lv << endl;

	UpdateStatue();
}

void Player::UpdateStatue()
{
	int updateMHP = BaseHP + _Lv * 10;
	int updateATK = BaseATK + _Lv * 5;

	MaxHP = updateMHP;
	atk = updateATK;
}

void Player::Revival()
{
	cur_hp = MaxHP;
}

void Player::MultiAttack(vector<Creature*> arr, int size)
{
	for (int i = 0; i < size; i++) {
		Attack(arr[i]);
	}
}
