#ifndef COMBAT_ENTITY
#define COMBAT_ENTITY

#include "entity.h"

class combatEntity : public Entity
{
    public:
    int attackLevel;
    int defenseLevel;
    int strengthLevel;
    combatEntity()
    {
        xpValue = 5;
        levelRequirement = 0;
    }

    
    ActionResult action() override; //double hitChance, int minHit, int maxHit) override;


};

class Goblin : public combatEntity
{
    public:
    Goblin(int numEntities)
    {
        count = numEntities;
        maxCount = numEntities;
        skillType = MELEE_COMBAT;
        name = "Goblin";
        maxHealth = 10;
        health = maxHealth;
        respawnTime = 5000;
        difficulty = 2;

        loot.addEntry(CoinsItem(), 1.00, 1, 2);
    }
};

#endif