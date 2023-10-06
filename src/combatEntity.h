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
        skillCategory = COMBAT;
        xpValue = 5;
        levelRequirement = 0;
    }

    
    ActionResult action(double hitChance, int minHit, int maxHit, SKILL_TYPE skillType) override;//double hitChance, int minHit, int maxHit) override;


};

class Goblin : public combatEntity
{
    public:
    Goblin(int id )
    {
        entId = id;
        count = 1;
        maxCount = 1;
        skillType = ATTACK;
        name = "Goblin";
        maxHealth = 10;
        health = maxHealth;
        respawnTime = 5000;
        difficulty = 2;

        loot.addEntry(0, 1.00, 1, 2);
    }
};

#endif