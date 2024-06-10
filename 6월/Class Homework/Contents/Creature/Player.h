#pragma once
class Player : public Creature
{
protected:
	int exp;

public:
	Player(string name, int hp, int afk);
	virtual ~Player();

};

