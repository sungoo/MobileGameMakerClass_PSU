#pragma once
#include "Creature.h"
class Knight :
    public Player
{
    bool furi;
public:
    Knight(string name, string major, int hp, int afk);
    virtual ~Knight();

    // Player을(를) 통해 상속됨
    virtual void Attack(Creature* other) override;
    void printInfo() override;
};

