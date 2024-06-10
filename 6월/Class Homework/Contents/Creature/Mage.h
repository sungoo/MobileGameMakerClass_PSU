#pragma once
#include "Player.h"
class Mage :
    public Player
{
    int mp;
public:
    Mage(string name, int hp, int mp, int atk);
    virtual ~Mage();

    // Player을(를) 통해 상속됨
    void Attack(Creature* other) override;

};

