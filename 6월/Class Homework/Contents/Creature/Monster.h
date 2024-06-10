#pragma once
#include "Creature.h"
class Monster :
    public Creature
{
public:
    Monster(string name, int hp, int afk);
    virtual ~Monster();

    // Creature을(를) 통해 상속됨
    virtual void Attack(Creature* other) override;
};

