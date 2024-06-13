#include "pch.h"
#include "Player.h"

Player::Player(string name, string major, int hp, int afk):
	Creature(name, major, hp, afk),
	exp(0)
{
}

Player::~Player()
{
}

void Player::Revival()
{
	cur_hp = MaxHP;
}
