#ifndef COMBAT_ENTITY
#define COMBAT_ENTITY

#include "entity.h"
#include "player.h"

class Player;
class Goblin;

class combatEntity : public Entity
{
    public:
    int attackLevel;
    int defenseLevel;
    int strengthLevel;
    int attackInterval; //in number of ticks
    int nextAttackTime;

    // refernce to the player that created this entity.
    // In group content this would be consolodated from mutliple
    // entites to a single entity. This entity would have a list 
    // of target players. 
    Player * playerTarget;

    combatEntity()
    {
        skillCategory = COMBAT;
        xpValue = 5;
        levelRequirement = 0;
    }

    
    ActionResult action(double hitChance, int minHit, int maxHit, SKILL_TYPE skillType) override;//double hitChance, int minHit, int maxHit) override;
    
    void  update() override;
    

};

class Goblin : public combatEntity
{
    public:
    Goblin(){}
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
        attackLevel = 1;
        attackInterval = 10;
    

        loot.addEntry(0, 1.00, 1, 2);
    }
};

#endif