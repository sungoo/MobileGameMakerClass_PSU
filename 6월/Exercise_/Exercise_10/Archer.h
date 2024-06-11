#pragma once
#include "Player.h"

class Archer : public Player
{
public:
	Archer(class Pet* pet);
	Archer(int hp);
	~Archer();

public:
	class Pet* _pet;
};

