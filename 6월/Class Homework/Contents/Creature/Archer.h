#pragma once
#include "Creature.h"
class Archer :
    public Player
{

public:
    Archer(string name, int hp, int afk);
    virtual ~Archer();

    // Player을(를) 통해 상속됨
    virtual void Attack(Creature* other) override;
};

