#pragma once
class Player : public Creature
{
protected:
	int exp;

public:
	Player(string name, string major, int hp, int afk);
	virtual ~Player();

};

