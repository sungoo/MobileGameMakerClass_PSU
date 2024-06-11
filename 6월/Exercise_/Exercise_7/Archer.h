#pragma once
#include "Player.h"

class Archer : public Player
{
public:
	Archer();
	Archer(int hp);
	virtual ~Archer();

public:
	Pet* _pet;
};

