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
    Tree(int numEntities)
    {
        count = numEntities;
        maxCount = numEntities;
        skillType = WOODCUTTING;
        levelRequirement = 1;
        name = "Tree";
        maxHealth = 10;
        health = maxHealth;
        respawnTime = 5000;
        difficulty = 2;
        xpValue = 5;

        printf("entity %s created\n", name.c_str());

        loot.addEntry(RegularLogsItem(), 1.00, 1, 2);


    }



};

#endif