#pragma once
#include "Player.h"

class Knight : public Player
{
public:
	Knight();
	Knight(int hp);
	~Knight();
	
	virtual void PrintInfo();

};

