#include "pch.h"
#include "Player.h"

Player::Player(string name, int hp, int afk):
	Creature(name, hp, afk),
	exp(0)
{
}

Player::~Player()
{
}
