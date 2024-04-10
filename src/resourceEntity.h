#ifndef RESOURCE_ENTITY
#define RESOURCE_ENTITY


#include "entity.h"


class ResourceEntity : public Entity
{
    public:
   
    ActionResult action(double hitChance, int minHit, int maxHit) override;

};

class Tree : public ResourceEntity
{
    public:
    Tree(int id)
    {
        entId = id;
        count = 1;
        maxCount = 1;
        skillType = WOODCUTTING;
        levelRequirement = 1;
        name = "Tree";
        maxHealth = 10;
        health = maxHealth;
        respawnTime = 5000;
        difficulty = 2;
        xpValue = 5;

        printf("entity %s created\n", name.c_str());

        loot.addEntry(1, 1.00, 1, 2);


    }



};

class OakTree : public ResourceEntity
{
    public:
    OakTree(int id)
    {
        entId = id;
        count = 1;
        maxCount = 1;
        skillType = WOODCUTTING;
        levelRequirement = 1;
        name = "Oak Tree";
        maxHealth = 10;
        health = maxHealth;
        respawnTime = 5000;
        difficulty = 2;
        xpValue = 5;

        printf("entity %s created\n", name.c_str());

        loot.addEntry((int)ItemIdEnum::ITEMS_OAKLOGS, 1.00, 1, 2);


    }



};

#endif