#pragma once
#include "Player.h"
class Mage :
    public Player
{
    int cur_mp;
    int MaxMP;
public:
    Mage(string name, string major, int hp, int mp, int atk);
    virtual ~Mage();

    // Player을(를) 통해 상속됨
    void Attack(Creature* other) override;
    void printInfo() override;
    void Revival() override;
};

